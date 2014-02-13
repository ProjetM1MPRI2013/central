#include"serverImplem.h"

#include <assert.h>
#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "debug.h"

/*
 * @author mheinric
 */

using namespace std ;
using namespace boost::asio ;


ServerImplem::ServerImplem(ServerInfo& s_info) : ComunicatorImplem(),
  client_endpoints(), registered_players(), sender_endpoint() {

  //connect socket
  ip::udp::resolver resolver(*service) ;
  ip::udp::resolver::query query(s_info.hostname, s_info.port) ;
  ip::udp::resolver::iterator addr_iter = resolver.resolve(query) ;
  if(addr_iter == ip::udp::resolver::iterator())
    {
      //Address not found ....
      LOG(error) << "Server failed to resolve address " << s_info.hostname << " port : " << s_info.port ;
      throw std::runtime_error("Address not found") ;
    }
  endpoint local_endpoint = *addr_iter ;
  sock->open(ip::udp::v4());
  sock->bind(local_endpoint);
  updateGen = NULL ;
  DBG << "SERVER: Created with address : " << local_endpoint.address().to_string()
      << ":" << local_endpoint.port() ;
  wait_receive();
}

ServerImplem::~ServerImplem(){
  if(updateGen != NULL)
    delete updateGen ;
}

vector<int> ServerImplem::getConnectedPlayers(){
  vector<int> players ;
  map<int,endpoint>::iterator it ;
  for(it = registered_players.begin() ; it != registered_players.end() ; it ++)
    {
      players.push_back(it->first);
    }
  return players ;
}

bool ServerImplem::isConnected(int player){
  return registered_players.find(player) != registered_players.end() ;
}

void ServerImplem::send_message(AbstractMessage &msg, bool reliable, string msgType, int player){
  //TODO : msg_id faux si il y a plusieurs clients (utilisé plusieurs fois)
  last_sent++ ;
  //asynchronous send requires that buffers are stored on the heap.
  //they are freed when the callback on_sent is called
  string* header = create_header(reliable, msgType, last_sent) ;
  string* data = new string(msg.toString()) ;

  if(player == -1)
    {
      //broadcast
      for(endpoint cli_endpoint : client_endpoints)
        {
          vector<string *> string_msg ;
          string_msg.push_back(new string(*header));
          string_msg.push_back(new string(*data));
          vector<const_buffer>buffs ;
          buffs.push_back(buffer(*string_msg[0]));
          buffs.push_back(buffer(*string_msg[1]));

          auto handler = boost::bind(&ServerImplem::on_sent, this,string_msg,cli_endpoint, _1, _2) ;
          write_buff(buffs, handler, &cli_endpoint) ;
        }
      //new objects were used at each turn of the loop.
      //the orignal ones can be deleted
      delete header ;
      delete data ;
    }
  else
    {
      //send to a given player
      assert(registered_players.find(player) != registered_players.end()) ;
      vector<string *> string_msg ;
      string_msg.push_back(header);
      string_msg.push_back(data);
      vector<const_buffer>buffs ;
      buffs.push_back(buffer(*string_msg[0]));
      buffs.push_back(buffer(*string_msg[1]));
      endpoint cli_endpoint = registered_players.at(player) ;
      auto handler = boost::bind(&ServerImplem::on_sent, this,string_msg,cli_endpoint, _1, _2) ;
      write_buff(buffs, handler, &cli_endpoint) ;

    }
}

std::vector<AbstractMessage *> ServerImplem::receive_messages(string msgType, AbstractMessage *(*f)(string &)){
  //copy of ClientImplem::receive_messages
  //Could not be in comunicatorImplem because this method is in the Client/Server interface
  mapType::iterator elts = received_messages.find(msgType) ;
  if(elts == received_messages.end())
      return vector<AbstractMessage*>();
  else
    {
      vector<AbstractMessage *> result ;
      for(string& msg : elts->second)
        {
          AbstractMessage* messagep = f(msg) ;
          if(NULL != messagep)
            result.push_back(messagep);
        }
      received_messages.erase(elts);
      return result ;
    }

}

void ServerImplem::on_sent(vector<string*> &data, endpoint cli_endpoint, const error_code &error, int){ 
  //TODO : verify that all the message was transmitted
  assert(data.size() >= 2) ;
  assert(data[0]->size() == HEADER_SIZE) ;

  if(is_shutdown)
    {
      //Server has shutdown -> free all memory and return as soos as possible
      for(string* p : data)
        delete p ;
      return ;
    }

  int id = get_msg_id(*data[0]) ;
  DBG << "SERVER: sent message with id : " << id << " and type " << get_msg_type(*data[0]);
  if(error != 0)
    {
      //Error occured
      LOG(error) << "SERVER: Send error occured : " << error.message() ;
      NetEvent msg(NetEvent::SEND_ERR) ;
      generate_message(msg) ;
      //free memory
      for(std::string* tbuff : data)
        {
          delete tbuff ;
        }
      return ;
    }

  //No error
  if(ack_message(*data[0]))
    {
      //ACK needed
      ack_set.insert(id) ;
      deadline_timer *t = new deadline_timer(*service) ;
      t->expires_from_now(boost::posix_time::millisec(TIME_TO_WAIT)) ;
      increase_tasks();
      t->async_wait(boost::bind(&ServerImplem::check_ack,this, data, cli_endpoint,1,t,_1)) ;
    }
  else
    {
      //No ACK : free memory
      for(std::string* tbuff : data)
        {
          delete tbuff ;
        }
    }

}

void ServerImplem::on_receive(const boost::system::error_code &error, int size){
  if(client_endpoints.insert(sender_endpoint).second)
    DBG << "SERVER: Added new Client with address : "
           << sender_endpoint.address().to_string() << ":" << sender_endpoint.port();
  int id = get_msg_id(*header_buff) ;
  DBG << "SERVER: Received message with id : " << id << " and type " << get_msg_type(*header_buff) ;

  if(is_shutdown)
    return ;

  if(error != 0)
    {
      LOG(error) << "SERVER: Error while sending message : " << error.message() ;
      generate_message(NetEvent(NetEvent::RECEIVE_ERR));
      wait_receive() ;
      return ;
    }
  if(ack_message(*header_buff))
    {
      //Handle Ack
      NetEvent e(NetEvent::ACK) ;
      e.setData(id) ;
      DBG << "SERVER: sending ACK with id : " << id << " for message " << e.getData();
      //TODO : bad il faudrait juste l'envoyer pas le broadcaster
      broadcastMessage<NetEvent>(e, false);
      bool b = sent_ack.insert(id).second ;

      if(!b)
        {
          //message dupicate
          DBG << "SERVER: Message received is a duplicate" ;
          wait_receive() ;
          return ;
        }
      else
        {
          //remove ack from set in the future (5 sec)
          deadline_timer timer(*service);
          timer.expires_from_now(boost::posix_time::seconds(5)) ;
          //No increase_tasks here : no memory management involved
          auto after_wait = [this, id](const boost::system::error_code){sent_ack.erase(id);} ;
          timer.async_wait(after_wait) ;
        }
      }
  std::string type = get_msg_type(*header_buff) ;
  if(type.compare(NetEvent::getMsgType()) == 0)
    {
      NetEvent *event = (NetEvent *) AbstractMessage::fromString(buff->substr(0,size - HEADER_SIZE)) ;

      DBG << "SERVER: NetEvent received : " << *event ;
      switch(event->getType())
        {
        case NetEvent::NOT_SET :
          {
            assert(false) ;
            break ;
          }

        case NetEvent::SERV_LOST :
          {
            assert(false) ;
            break ;
          }

        case NetEvent::SERV_TRY :
          {
            //Not using sendMessage, because don't know player id to send to...
            NetEvent reply(NetEvent::SERV_RESP) ;
            string *msg_body = new string(reply.toString()) ;
            last_sent ++ ;
            string *msg_header = create_header(false, NetEvent::getMsgType(), last_sent) ;
            vector<const_buffer> buffers ;
            buffers.push_back(buffer(*msg_header));
            buffers.push_back(buffer(*msg_body));
            auto handler = [this, msg_header, msg_body](const error_code&, int)
                                {
                                   delete msg_header ;
                                   delete msg_body ;
                                } ;
            write_buff(buffers, handler, &sender_endpoint);
            break ;
          }

        case NetEvent::SERV_RESP :
          {
            assert(false) ;
            break ;
          }

        case NetEvent::CLI_LOST :
          {
            assert(false) ;
            break ;
          }

        case NetEvent::CLI_TRY:
          {
            assert(false) ;
            break ;
          }

        case NetEvent::CLI_RESP :
          {
            break ;
          }

        case NetEvent::MSG_LOST :
          {
            break ;
          }

        case NetEvent::PLAYER_JOIN :
          {
            registered_players[event->getData()] = sender_endpoint ;
            break ;
          }

        case NetEvent::PLAYER_QUIT :
          {
            if(registered_players.find(event->getData()) != registered_players.end())
              registered_players.erase(event->getData());
            break ;
          }

        case NetEvent::SEND_ERR :
          {
            assert(false) ;
            break ;
          }

        case NetEvent::RECEIVE_ERR :
          {
            assert(false) ;
            break ;
          }
        case NetEvent::ACK :
          {
            int idrec = event->getData() ;
            DBG << "SERVER: received ACK for message " << idrec ;
            if(ack_set.find(idrec) != ack_set.end())
              ack_set.erase(idrec) ;
            delete event ;
            wait_receive() ;
            return ;
            break ;
          }
        }
        delete event ;
    }
  received_messages[type].push_back(buff->substr(0,size - HEADER_SIZE)) ;
  wait_receive() ;
}


void ServerImplem::check_ack(std::vector<std::string*>& msg, endpoint cli_endpoint ,
                   int nb_times, deadline_timer *t, const boost::system::error_code &err) {
  assert(msg.size() >= 2) ;
  assert(msg[0]->size() == HEADER_SIZE) ;

  decrease_tasks();
  if(is_shutdown)
    {
      //Server has shutdown -> free all memory and return as soos as possible
      for(string* p : msg)
        delete p ;
      delete t ;
      return ;
    }

  int id = get_msg_id(*msg[0]) ;
  set<int>::iterator it = ack_set.find(id) ;
  if(it == ack_set.end())
    {
      //ACK received
      //free memory
      delete t ;
      for(string* p : msg)
          delete p ;
    }
  else
    {
      //No ack
      if(nb_times >= NB_TRY)
        {
          //Cannot reach server
          LOG(warning) << "SERVER: could not reach client in time" ;
          generate_message(NetEvent(NetEvent::SERV_LOST));
          //free memory
          delete t ;
          for(string* p : msg)
            delete p ;
        }
      else
        {
          //Resend
          DBG << "SERVER: No ACK, resending message with id : " << id << "and type " << get_msg_type(*msg[0]);
          vector<const_buffer> msg_buff ;
          for(string* p : msg)
            msg_buff.push_back(buffer(*p));

          write_buff(msg_buff,[this](boost::system::error_code,int){}, &cli_endpoint) ;
          t->expires_from_now(boost::posix_time::millisec(TIME_TO_WAIT)) ;
          increase_tasks();
          t->async_wait(boost::bind(&ServerImplem::check_ack,this, msg, cli_endpoint,nb_times +1,t,_1)) ;
        }
    }
}


void ServerImplem::wait_receive(){
  vector<mutable_buffer> vec ;
  //hack : using the underlying c_str of a string as a buffer (in theory, read only).
  vec.push_back(buffer((char *) header_buff-> c_str(), HEADER_SIZE));
  vec.push_back(buffer((char *) buff-> c_str(), BUFF_SIZE));
  sock->async_receive_from(vec, sender_endpoint, boost::bind(&ServerImplem::on_receive,this,_1,_2)) ;
}

void ServerImplem::setSimulation(GlobalState *simu) {
  if(updateGen != NULL)
    LOG(error) << "SERVER: Simulation already set" ;
  updateGen = new UpdateGenerator(simu, this) ;
}

void ServerImplem::update(sf::Time dt) {
  if(updateGen == NULL)
    LOG(warning) << "SERVER: Cannot update, no Simulation attached" ;
  else
    updateGen->update(dt);
}
