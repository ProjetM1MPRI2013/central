#include "chat_event.h"
#include "assert.h"

const std::string ChatEvent::MSG_TYPE = "chatevent" ;

ChatEvent::ChatEvent() {
	data = "";
}

std::string ChatEvent::getMsgType(){
  return MSG_TYPE ;
}

std::string& ChatEvent::toString(){
  //not implemented yet
  assert(false) ;
}

ChatEvent* ChatEvent::fromString(std::string &msg){
  //not implemented yet
  assert(false) ;
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
