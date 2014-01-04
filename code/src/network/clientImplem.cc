#include <boost/bind.hpp>
#include <assert.h>

#include "clientImplem.h"



using namespace boost::asio ;
using namespace std ;


ClientImplem::ClientImplem(ClientInfo c_info) : last_sent(0), server_endpoint(), ack_set(),received_messages() {

  //Not implemented yet
  assert(false) ;

    //init fields
    service = new io_service() ;
    sock = new ip::udp::socket(*service) ;
    buff = new vector<char>(BUFF_SIZE, '\000') ;
    header_buff = new vector<char>(HEADER_SIZE, '\000') ;

    //connect socket
    ip::udp::resolver resolver(*service) ;
    ip::udp::resolver::query query(c_info.serverName, c_info.serverPort) ;
    server_endpoint = *resolver.resolve(query) ;
    if(c_info.localName.compare(""))
    {
        //a local address is provided
        ip::udp::resolver::query query2(c_info.localName,c_info.localPort) ;
        ip::udp::endpoint local_endpoint = *resolver.resolve(query2) ;
        sock->bind(local_endpoint) ;
        sock->open(ip::udp::v4()) ;
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

    NetEvent startMsg(NetEvent::SERV_TRY) ;
    this->sendMessage<NetEvent>(startMsg) ;
}


ClientImplem::~ClientImplem(){

    shutdown() ;
    delete service ;
    delete sock ;
    delete buff ;
    delete header_buff ;
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
    }
  else
    {
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
}



void ClientImplem::on_recieve(const boost::system::error_code &error, int){
  //TODO : send ack to server if necessary
    if(error != 0)
    {
        generate_message(NetEvent(NetEvent::RECEIVE_ERR));
        vector<mutable_buffer> vec ;
        vec.push_back(buffer(*header_buff, HEADER_SIZE));
        vec.push_back(buffer(*buff, BUFF_SIZE));
        wait_receive() ;
        return ;
    }
    std::string type = get_msg_type(string(header_buff->begin(), header_buff->end())) ;
    if(type.compare(NetEvent::getMsgType()) == 0)
      {
        //Handle NetEvent
        //TODO : change that without the copy
        NetEvent *event = NetEvent::fromString(string(buff->begin(), buff->end())) ;
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
          }
      }
    received_messages[type].push_back(new std::string(buff->begin(), buff->end())) ;
    wait_receive() ;
}

void ClientImplem::shutdown(){
  //TODO
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
             {
               delete p ;
             }
         }
       else
         {
           //Resend
           vector<const_buffer> msg_buff ;
           for(string* p : msg)
             msg_buff.push_back(buffer(*p));
           sock->async_send(msg_buff, boost::bind(&ClientImplem::check_sent,this, _1, _2)) ;
           t->expires_from_now(boost::posix_time::millisec(TIME_TO_WAIT)) ;
           t->async_wait(boost::bind(&ClientImplem::check_ack,this, msg, nb_times +1,t,_1)) ;
         }
     }
 }

 std::string ClientImplem::get_msg_type(const string &header) {
   assert(header.size() == HEADER_SIZE) ;
   return header.substr(0, 8) ;
 }

 int ClientImplem::get_msg_id(const string &header) {
   string id_s = header.substr(8,4) ;
   int res = 0 ;
   for(int i = 0 ; i < 4 ; i++)
     {
       res = 256*res + ((int) id_s.at(i)) ;
     }
   return res ;
 }


 void ClientImplem::generate_message(NetEvent event) {
   received_messages[NetEvent::getMsgType()].push_back(&event.toString()) ;
 }

 bool ClientImplem::ack_message(const string &header) {
   assert(header.size() == HEADER_SIZE) ;
   return (header[HEADER_SIZE -1] != '\000') ;
 }

std::string* ClientImplem::create_header(bool reliable, std::string type, int id) {
  //TODO
  return new std::string() ;
}

void ClientImplem::wait_receive(){
  vector<mutable_buffer> vec ;
  vec.push_back(buffer(*header_buff, HEADER_SIZE));
  vec.push_back(buffer(*buff, BUFF_SIZE));
  sock->async_receive(vec, boost::bind(&ClientImplem::on_recieve,this,_1,_2)) ;
}
