#include "netEvent.h"
#include "assert.h"

const std::string NetEvent::MSG_TYPE = "netEvent" ;

NetEvent::NetEvent() : data(0), type(NetEvent::NOT_SET){}

NetEvent::NetEvent(Type type) : data(0), type(type){}

std::string NetEvent::getMsgType(){
  return MSG_TYPE ;
}

std::string& NetEvent::toString(){
  //not implemented yet
  assert(false) ;
}

NetEvent* NetEvent::fromString(std::string &msg){
  //not implemented yet
  assert(false) ;
}

NetEvent * NetEvent::copy(){
  NetEvent * event = new NetEvent() ;
  event->setType(this->getType());
  event->data = this->data ;
  return event ;
}
