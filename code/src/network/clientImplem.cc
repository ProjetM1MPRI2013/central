#include <boost/bind.hpp>
#include <assert.h>

#include "clientImplem.h"



using namespace boost::asio ;
using namespace std ;


ClientImplem::ClientImplem(ClientInfo &c_info) : ComunicatorImplem(), server_endpoint() {

    //connect socket
    ip::udp::resolver resolver(*service) ;
    ip::udp::resolver::query query(c_info.serverName, c_info.serverPort) ;
    server_endpoint = *resolver.resolve(query) ;
    if(c_info.localName.compare("") != 0)
    {
        //a local address is provided
        ip::udp::resolver::query query2(c_info.localName,c_info.localPort) ;
        ip::udp::endpoint local_endpoint = *resolver.resolve(query2) ;
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
    this->sendMessage<NetEvent>(startMsg) ;
    wait_receive();
}


ClientImplem::~ClientImplem(){
}


void ClientImplem::send_message(AbstractMessage &msg, bool reliable, string msgType){
  last_sent ++ ;
  string* header = create_header(reliable, msgType, last_sent) ;
  string& data = msg.toString() ;
  vector<const_buffer> msg_buff ;
  msg_buff.push_back(buffer(*header));
  msg_buff.push_back(buffer(data));

  vector<string*> buffers ;
  buffers.push_back(header);
  buffers.push_back(&data);
  sock->async_send(msg_buff, boost::bind(&ClientImplem::on_sent, this,buffers, _1,_2)) ;

  return ;
}

std::vector<AbstractMessage *> ClientImplem::receive_messages(string msgType, AbstractMessage *(*f)(string &)){
  //copy of ServerImplem::receive_messages
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


void ClientImplem::on_sent(std::vector<std::string *>& data, const error_code& error, int){
  cout << "INFO : Message sent to server" << endl ;
  cout << "INFO : Message Type : " << get_msg_type(*data[0]) << endl ;
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
      cout << "NetWork ERROR : " << error.message() << endl ;
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



void ClientImplem::on_receive(const boost::system::error_code &error, int){
  wait_receive() ;
  if(error != 0)
    {
      generate_message(NetEvent(NetEvent::RECEIVE_ERR));
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
            //auto after_wait /*const boost::system::error_code*/ =
            //			boost::bind(&set<int>::erase, sent_ack, id) ;
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
              this->sendMessage<NetEvent>(e) ;
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
}



void ClientImplem::check_ack(std::vector<std::string*>& msg,
                             int nb_times, deadline_timer *t,
                             const boost::system::error_code &err) {
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
        {
          delete p ;
        }
    }
  else
    {
      //No ack
      if(nb_times >= NB_TRY)
        {
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
          vector<const_buffer> msg_buff ;
          for(string* p : msg)
            msg_buff.push_back(buffer(*p));

          sock->async_send(msg_buff, [](boost::system::error_code,int){}) ;
          t->expires_from_now(boost::posix_time::millisec(TIME_TO_WAIT)) ;
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
