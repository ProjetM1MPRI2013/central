#include <sstream>
#include "assert.h"

#include "netEvent.h"
#include <boost/serialization/export.hpp>

#include "debug.h"

using namespace std ;
using namespace boost::archive ;

const string NetEvent::MSG_TYPE = "NetEvent" ;

NetEvent::NetEvent() :  type(NetEvent::NOT_SET), data(0) {}

NetEvent::NetEvent(Type type) : type(type), data(0) {}

/*
string NetEvent::getMsgType(){
  return MSG_TYPE ;
}
*/
/*
string NetEvent::toString(){
  stringstream ss ;
  {
    NetEvent* nete = copy() ;
    text_oarchive ar(ss) ;
    ar << nete ;
    delete nete ;
  }
  DBG << "NetEvent serialize to : " << ss.str() ;
  DBG << "Initial message : " << *this ;
  return ss.str() ;
}

NetEvent* NetEvent::fromString(const string &msg){
  DBG << "NetEvent deserialize from : " << msg ;
  stringstream ss(msg) ;
  text_iarchive ar(ss) ;
  NetEvent* e = NULL ;
  ar >> e ;
  DBG << *e ;
  return e ;
}
*/
NetEvent * NetEvent::copy(){
  NetEvent * event = new NetEvent() ;
  event->setType(this->getType());
  event->data = this->data ;
  return event ;
}

ostream& operator<<(std::ostream& os, const NetEvent& obj) {
  os << "Event Type : " ;
  switch(obj.getType())
    {
    case NetEvent::ACK:
      os << "ACK, " ;
      break;
    case NetEvent::CLI_LOST:
      os << "CLI_LOST, " ;
      break;
    case NetEvent::CLI_RESP:
      os << "CLI_RESP, " ;
      break;
    case NetEvent::CLI_TRY:
      os << "CLI_TRY, " ;
      break;
    case NetEvent::MSG_LOST:
      os << "MSG_LOST, " ;
      break;
    case NetEvent::NOT_SET:
      os << "NOT_SET, " ;
      break;
    case NetEvent::PLAYER_JOIN:
      os << "PLAYER_JOIN, " ;
      break;
    case NetEvent::PLAYER_QUIT:
      os << "PLAYER_QUIT, " ;
      break;
    case NetEvent::RECEIVE_ERR:
      os << "RECEIVE_ERR, " ;
      break;
    case NetEvent::SEND_ERR:
      os << "SEND_ERR, " ;
    case NetEvent::SERV_LOST:
      os << "SERV_LOST, " ;
      break;
    case NetEvent::SERV_RESP:
      os << "SERV_RESP, " ;
      break;
    case NetEvent::SERV_TRY:
      os << "SERV_TRY, " ;
      break;
    }
  os << "Data : " << obj.getData() ;
  return os ;
}
