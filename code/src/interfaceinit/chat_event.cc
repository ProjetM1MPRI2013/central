#include "chat_event.h"
#include "assert.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <sstream>

BOOST_CLASS_EXPORT(ChatEvent)

const std::string ChatEvent::MSG_TYPE = "chateven" ;

ChatEvent::ChatEvent() {
	data = "";
}
ChatEvent::ChatEvent(const ChatEvent& tobecopied) {
  this->data = std::string(tobecopied.data);
}
std::string ChatEvent::getMsgType(){
  return MSG_TYPE ;
}

std::string ChatEvent::toString(){
  std::stringstream ss ;
  boost::archive::text_oarchive ar(ss) ;
  ChatEvent * this2 = this;
  ar << this2 ;
  return ss.str() ;
}

ChatEvent* ChatEvent::fromString(std::string &msg){
  std::stringstream ss(msg) ;
  boost::archive::text_iarchive ar(ss) ;
  ChatEvent* event = NULL ;
  ar >> event ;
  return event ;
}
void ChatEvent::setData(std::string dataString) {
	this->data = dataString;
}
std::string ChatEvent::getData() {
	return (this->data);
}
ChatEvent* ChatEvent::copy(){
  ChatEvent * event = new ChatEvent() ;
  event->setData(this->getData());
  return event ;
}
