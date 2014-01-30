#include "chat_event.h"
#include "assert.h"

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
  return data;
}

ChatEvent* ChatEvent::fromString(std::string &msg){
  ChatEvent* event = new ChatEvent() ;
  event->setData(msg) ;
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
