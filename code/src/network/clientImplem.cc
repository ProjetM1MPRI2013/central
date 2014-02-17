#include <boost/bind.hpp>
#include <assert.h>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>
#include <boost/thread/mutex.hpp>

#include "clientImplem.h"
#include "debug.h"
#include "simulation/localState.h"

/*
 * @author mheinric
 */

using namespace boost::asio ;
using namespace std ;


ClientImplem::ClientImplem(ClientInfo &c_info) : ComunicatorImplem(), server_endpoint(),
  locStateUpdater(NULL){

    //connect socket
    ip::udp::resolver resolver(*service) ;
    ip::udp::resolver::query query(ip::udp::v4(), c_info.serverName, c_info.serverPort,
                                   ip::udp::resolver::query::passive) ;
    ip::udp::resolver::iterator addr_iter = resolver.resolve(query) ;
    if(addr_iter == ip::udp::resolver::iterator())
      {
        //Address not found ....
        LOG(error) << "Client failed to resolve Server address " << c_info.serverName << " port : " << c_info.serverPort ;
        throw std::runtime_error("Address not found") ;
      }
    server_endpoint = *addr_iter ;
    if(c_info.localName.compare("") != 0)
    {
        //a local address is provided
        ip::udp::resolver::query query2(ip::udp::v4(), c_info.localName,c_info.localPort,
                                        ip::udp::resolver::query::passive) ;
        addr_iter = resolver.resolve(query2) ;
        if(addr_iter == ip::udp::resolver::iterator())
          {
            //Address not found ....
            LOG(error) << "Client failed to resolve Server address " << c_info.serverName << " port : " << c_info.serverPort ;
            throw std::runtime_error("Address not found") ;
          }
        ip::udp::endpoint local_endpoint = *addr_iter ;
        sock->open(ip::udp::v4()) ;
        sock->bind(local_endpoint) ;
    }
    else
    {
        //no local address provided
        sock->open(ip::udp::v4()) ;
        ip::udp::endpoint local_endpoint = sock->local_endpoint() ;
        c_info.localName = local_endpoint.address().to_string();
        int port = local_endpoint.port() ;
        ostringstream os ;
        os << port ;
        c_info.localPort = os.str() ;
    }
    sock->connect(server_endpoint);
    NetEvent startMsg(NetEvent::SERV_TRY) ;
    this->sendMessage<NetEvent>(startMsg, false) ;
    wait_receive();
}


ClientImplem::~ClientImplem(){
  if(locStateUpdater != NULL)
    delete locStateUpdater ;
}


void ClientImplem::send_message(AbstractMessage &msg, bool reliable, string msgType){
  last_sent ++ ;
  //asynchronous send requires buffers to be saved on the heap as their
  //content may be used after sock->async_send() returns.
  //they are deleted when the callback on_sent is called
  string* header = create_header(reliable, msgType, last_sent) ;
  string* data = new string(msg.toString()) ;
  vector<const_buffer> msg_buff ;
  msg_buff.push_back(buffer(*header));
  msg_buff.push_back(buffer(*data));

  vector<string*> buffers ;
  buffers.push_back(header);
  buffers.push_back(data);

  write_buff(msg_buff, [this, buffers](const error_code& e, int i){on_sent(buffers, e,i) ;}) ;

  return ;
}

std::vector<AbstractMessage *> ClientImplem::receive_messages(string msgType, AbstractMessage *(*f)(string &)){
  //copy of ServerImplem::receive_messages
  //Could not be in comunicatorImplem because this method is in the Client/Server interface

  received_messages_mutex.lock() ;
  mapType::iterator elts = received_messages.find(msgType) ;
  if(elts == received_messages.end())
    {
      received_messages_mutex.unlock() ;
      return vector<AbstractMessage*>();
    }
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
      received_messages_mutex.unlock() ;
      return result ;
    }

}


void ClientImplem::on_sent(const std::vector<std::string *>& data, const boost::system::error_code& error, int){
  int id = get_msg_id(*data[0]) ;
  DBG << "CLI: Message sent to server with id " << id << "and type " << get_msg_type(*data[0]) ;
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
      LOG(error) << "CLI: " << error.message() << endl ;
      return ;
    }
  if(is_shutdown)
    {
      //Client has shutdown -> free all memory and return as soos as possible
      for(string* p : data)
        delete p ;
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
      t->async_wait(boost::bind(&ClientImplem::check_ack,this, data, 1,t,_1)) ;
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



void ClientImplem::on_receive(const boost::system::error_code &error, int size){
  int id = get_msg_id(*header_buff) ;
  DBG << "CLI: Received Message with id " << id << " and type " << get_msg_type(*header_buff);

  if(error != 0)
    {
      generate_message(NetEvent(NetEvent::RECEIVE_ERR));
      wait_receive() ;
      return ;
    }
  if(is_shutdown)
    return ;

  if(ack_message(*header_buff))
    {
        //Handle Ack
        NetEvent e(NetEvent::ACK) ;
        e.setData(id) ;
        DBG << "CLI: Sending back ACK with id " << id << " for message " << e.getData();
        sendMessage<NetEvent>(e, false);
        bool b = sent_ack.insert(id).second ;

        if(!b)
          {
            //message dupicate
            wait_receive() ;
            return ;
          }
        else
          {
            //remove ack from set in the future (3 sec)
            deadline_timer timer(*service);
            timer.expires_from_now(boost::posix_time::seconds(3)) ;
            //No increase task here : no memory management involved
            auto after_wait = [this, id](const boost::system::error_code){sent_ack.erase(id);} ;
            timer.async_wait(after_wait) ;
          }
    }
    std::string type = get_msg_type(*header_buff) ;
    if(type.compare(NetEvent::getMsgType()) == 0)
      {
        NetEvent *event = (NetEvent *) AbstractMessage::fromString(buff->substr(0,size - HEADER_SIZE)) ;
        DBG << "CLI: NetEvent received :" << *event ;
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
              assert(false) ;
              break ;
            }

          case NetEvent::SERV_RESP :
            {
              break ;
            }

          case NetEvent::CLI_LOST :
            {
              assert(false) ;
              break ;
            }

          case NetEvent::CLI_TRY:
            {
              NetEvent e(NetEvent::CLI_RESP) ;
              this->sendMessage<NetEvent>(e, false) ;
              break ;
            }

          case NetEvent::CLI_RESP :
            {
              assert(false) ;
              break ;
            }

          case NetEvent::MSG_LOST :
            {
              break ;
            }

          case NetEvent::PLAYER_JOIN :
            {
              break ;
            }

          case NetEvent::PLAYER_QUIT :
            {
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
              DBG << "CLI: received ACK for message " << idrec ;
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
    received_messages_mutex.lock() ;
    received_messages[type].push_back(buff->substr(0,size - HEADER_SIZE)) ;
    received_messages_mutex.unlock() ;
    wait_receive() ;
}



void ClientImplem::check_ack(std::vector<std::string*>& msg,
                             int nb_times, deadline_timer *t,
                             const boost::system::error_code &err) {
  assert(msg.size() >= 2) ;
  assert(msg[0]->size() == HEADER_SIZE) ;

  decrease_tasks();
  if(is_shutdown)
    {
      //Client has shutdown -> free all memory and return as soos as possible
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
        {
          delete p ;
        }
    }
  else
    {
      //No ack
      if(nb_times >= NB_TRY)
        {
          LOG(warning) << "CLI: Failed to reach server in time" ;
          //Cannot reach server
          generate_message(NetEvent::SERV_LOST);
          //free memory
          delete t ;
          for(string* p : msg)
              delete p ;
        }
      else
        {
          //Resend
          DBG << "CLI: No ACK received for message " << id  << " and type " << get_msg_type(*msg[0]) << ", re-sending message" ;
          vector<const_buffer> msg_buff ;
          for(string* p : msg)
            msg_buff.push_back(buffer(*p));

          //potentially dangerous : send can occur after the buffers are freed because ack received
          write_buff(msg_buff, [](const error_code&,int){}) ;
          t->expires_from_now(boost::posix_time::millisec(TIME_TO_WAIT)) ;
          increase_tasks();
          t->async_wait(boost::bind(&ClientImplem::check_ack,this, msg, nb_times +1,t,_1)) ;
        }
    }
}



void ClientImplem::wait_receive(){
  vector<mutable_buffer> vec ;
  //hack : using the underlying c_str of a string as a buffer (in theory, read only).
  vec.push_back(buffer((char *) header_buff-> c_str(), HEADER_SIZE));
  vec.push_back(buffer((char *) buff-> c_str(), BUFF_SIZE));
  sock->async_receive(vec, boost::bind(&ClientImplem::on_receive,this,_1,_2)) ;
}

void ClientImplem::setLocalState(LocalState *simu) {
  if(locStateUpdater != NULL)
    LOG(error) << "CLIENT: LocalState already set" ;
  locStateUpdater = new LocalStateUpdater(simu, this) ;
  NetEvent coevent(NetEvent::PLAYER_JOIN) ;
  coevent.setData(simu->getPlayer()->getID());
  sendMessage<NetEvent>(coevent) ;
}

void ClientImplem::update(sf::Time dt) {
  if(locStateUpdater == NULL)
    LOG(warning) << "CLIENT: Cannot update, no Local State attached" ;
  else
    locStateUpdater->update(dt);
}
