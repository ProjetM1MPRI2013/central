#include <sstream>
#include "assert.h"

#include "netEvent.h"

using namespace std ;
using namespace boost::archive ;

const string NetEvent::MSG_TYPE = "netEvent" ;

NetEvent::NetEvent() :  type(NetEvent::NOT_SET), data(0) {}

NetEvent::NetEvent(Type type) : type(type), data(0) {}

string NetEvent::getMsgType(){
  return MSG_TYPE ;
}

string& NetEvent::toString(){
  stringstream ss ;
  text_oarchive ar(ss) ;
  ar << *this ;
  return *(new string(ss.str())) ;
}

NetEvent* NetEvent::fromString(const string &msg){
  stringstream ss(msg) ;
  text_iarchive ar(ss) ;
  NetEvent* e = new NetEvent() ;
  ar >> *e ;
  return e ;
}

NetEvent * NetEvent::copy(){
  NetEvent * event = new NetEvent() ;
  event->setType(this->getType());
  event->data = this->data ;
  return event ;
}
