#include "clientImplem.h"
#include <boost/bind.hpp>


using namespace boost::asio ;
using namespace std ;


ClientImplem::ClientImplem(ClientInfo c_info) :ack_set(), received_messages() {

    //init fields
    service = new io_service() ;
    sock = new ip::udp::socket(*service) ;
    buff = new string(BUFF_SIZE, '\000') ;
    header_buff = new string(HEADER_SIZE, '\000') ;

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

    this->sendMessage<NetEvent>(*(new NetEvent(NetEvent::SERV_TRY))) ;
}


ClientImplem::~ClientImplem(){

    shutdown() ;
    delete service ;
    delete sock ;
    delete buff ;
    delete header_buff ;
}

void ClientImplem::on_sent(std::vector<std::string *>& data, const error_code& error, int){

  //TODO : verify that all the message was transmitted
  if(error != 0)
    {
      //Error occured
      NetEvent * msg = new NetEvent(NetEvent::SEND_ERR) ;
      generate_message(*msg) ;
      delete msg ;
      return ;
    }
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
      //No ACK
      return ;
    }
}



void ClientImplem::on_recieve(const boost::system::error_code &error, int){
    if(error != 0)
    {
        NetEvent * msg = new NetEvent(NetEvent::RECEIVE_ERR) ;
        generate_message(*msg);
        delete msg ;
        vector<mutable_buffer> vec ;
        vec.push_back(buffer(header_buff, HEADER_SIZE));
        vec.push_back(buffer(buff, BUFF_SIZE));
        sock->async_receive(vec, boost::bind(&ClientImplem::on_recieve,this,_1,_2)) ;
        return ;

    }
    //TODO : not implemented from here.

    /*
    if()
    int type = get_msg_type(*header_buff) ;
    switch(type)
    {
    case 0 :
    {
        //Connexion message
        break ;
    }
    case 1 :
    {
        //ack
        int nb = get_msg_nb(*buff) ;
        set<int>::iterator i = ack_set.find(nb) ;
        if(i != ack_set.end())
        {
            ack_set.erase(i);
        }
        break ;
    }
    case 2 :
    {
        //game Event
        break ;
    }
    case 3 :
    {
        //game update
        //see if we pass all the buffer, or only the interesting part
        GameUpdate &gu = GameUpdate::fromString(*buff) ;
        recieved_updates->push_back(gu);
        break ;
    }
    default :
    {
        break ;
    }

    } */

}

void ClientImplem::shutdown(){

}

 void ClientImplem::check_ack(std::vector<std::string*>& msg, int nb_times, deadline_timer *t, const boost::system::error_code &err) {}

 std::string ClientImplem::get_msg_type(std::string &header) {}

 int ClientImplem::get_msg_id(std::string & header) {}


 void ClientImplem::generate_message(NetEvent& event) {}

 bool ClientImplem::ack_message(std::string& header) {}

