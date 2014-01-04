#include "netEvent.h"
#include "assert.h"

const std::string NetEvent::MSG_TYPE = "netEvent" ;

NetEvent::NetEvent() :  type(NetEvent::NOT_SET), data(0) {}

NetEvent::NetEvent(Type type) : type(type), data(0) {}

std::string NetEvent::getMsgType(){
  return MSG_TYPE ;
}

std::string& NetEvent::toString(){
  //not implemented yet
  assert(false) ;
}

NetEvent* NetEvent::fromString(const std::string &msg){
  //not implemented yet
  assert(false) ;
}

NetEvent * NetEvent::copy(){
  NetEvent * event = new NetEvent() ;
  event->setType(this->getType());
  event->data = this->data ;
  return event ;
}
