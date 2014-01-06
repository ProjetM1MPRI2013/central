#include"serverImplem.h"

#include <assert.h>
#include <boost/bind.hpp>

using namespace std ;
using namespace boost::asio ;


ServerImplem::ServerImplem(ServerInfo& s_info) : ComunicatorImplem(),
  client_endpoints(), registered_players(), sender_endpoint() {

  //connect socket
  ip::udp::resolver resolver(*service) ;
  ip::udp::resolver::query query(s_info.hostname, s_info.port) ;
  endpoint local_endpoint = *resolver.resolve(query) ;
  sock->bind(local_endpoint);
  sock->open(ip::udp::v4());
}

ServerImplem::~ServerImplem(){

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
  last_sent++ ;
  string* header = create_header(reliable, msgType, last_sent) ;
  string* data = &msg.toString() ;
  vector<string *> string_msg ;


  vector<const_buffer>buffs ;
  buffs.push_back(buffer(*header));
  buffs.push_back(buffer(*data));

  if(player == -1)
    {
      //broadcast
      for(endpoint cli_endpoint : client_endpoints)
        {
          string_msg.push_back(new string(*header));
          string_msg.push_back(new string(*data));
          auto handler = boost::bind(&ServerImplem::on_sent, this,string_msg,cli_endpoint, _1, _2) ;
          sock->async_send_to(buffs, cli_endpoint, handler) ;
        }
      delete header ;
      delete data ;
    }
  else
    {
      //send to a given player
      string_msg.push_back(header);
      string_msg.push_back(data);
      endpoint cli_endpoint = registered_players.at(player) ;
      auto handler = boost::bind(&ServerImplem::on_sent, this,string_msg,cli_endpoint, _1, _2) ;
      sock->async_send_to(buffs, cli_endpoint, handler) ;
    }
}

std::vector<AbstractMessage *> ServerImplem::receive_messages(string msgType, AbstractMessage *(*f)(string &)){
  //copy of ClientImplem::receive_messages
  //Could not be in comunicatorImplem because this method is in the Client/Server interface
  mapType::iterator elts = received_messages.find(msgType) ;
  if(elts == received_messages.end())
    {
      return vector<AbstractMessage*>();
    }
  else
    {
      vector<AbstractMessage *> result ;
      for(string* msg : elts->second)
        {
          result.push_back(f(*msg));
          delete msg ;
        }
      received_messages.erase(elts);
      return result ;
    }

}

void ServerImplem::on_sent(vector<string*> &data, endpoint cli_endpoint, const error_code &error, int){
  //TODO : verify that all the message was transmitted
  assert(data.size() >= 2) ;
  assert(data[0]->size() == HEADER_SIZE) ;
  if(error != 0)
    {
      //Error occured
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
      int id = get_msg_id(*data[0]) ;
      ack_set.insert(id) ;
      deadline_timer *t = new deadline_timer(*service) ;
      t->expires_from_now(boost::posix_time::millisec(TIME_TO_WAIT)) ;
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

void ServerImplem::on_receive(const boost::system::error_code &error, int){
    if(error != 0)
    {
        generate_message(NetEvent(NetEvent::RECEIVE_ERR));
        wait_receive() ;
        return ;
    }
    if(ack_message(*header_buff))
      {
        //Handle Ack
        NetEvent e(NetEvent::ACK) ;
        int id = get_msg_id(*header_buff) ;
        e.setData(id) ;
        sendMessage<NetEvent>(e, false);
        bool b = sent_ack.insert(id).second ;

        if(!b)
          {
            //message dupicate
            return ;
          }
        else
          {
            //remove ack from set in the future (3 sec)
            deadline_timer timer(*service);
            timer.expires_from_now(boost::posix_time::seconds(3)) ;
            auto after_wait = [this, id](const boost::system::error_code){sent_ack.erase(id);} ;
            timer.async_wait(after_wait) ;
          }
      }
    std::string type = get_msg_type(*header_buff) ;
    if(type.compare(NetEvent::getMsgType()) == 0)
      {
        //Handle NetEvent
        NetEvent *event = NetEvent::fromString(*buff) ;
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
              NetEvent reply(NetEvent::SERV_RESP) ;
              string *reply_msg = &reply.toString() ;
              sock->async_send_to(buffer(*reply_msg),sender_endpoint,
                                  [reply_msg](const error_code,int){delete reply_msg;}) ;
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
              int id = event->getData() ;
              if(ack_set.find(id) != ack_set.end())
                ack_set.erase(id) ;
              delete event ;
              return ;
              break ;
            }
          }
      }
    received_messages[type].push_back(new std::string(*buff)) ;
    wait_receive() ;
}


void ServerImplem::check_ack(std::vector<std::string*>& msg, endpoint cli_endpoint ,
                   int nb_times, deadline_timer *t, const boost::system::error_code &err) {
  assert(msg.size() >= 2) ;
  assert(msg[0]->size() == HEADER_SIZE) ;
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
          generate_message(NetEvent(NetEvent::SERV_LOST));
          //free memory
          delete t ;
          for(string* p : msg)
            delete p ;
        }
      else
        {
          //Resend
          vector<const_buffer> msg_buff ;
          for(string* p : msg)
            msg_buff.push_back(buffer(*p));

          sock->async_send_to(msg_buff, cli_endpoint,[](boost::system::error_code,int){}) ;
          t->expires_from_now(boost::posix_time::millisec(TIME_TO_WAIT)) ;
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
