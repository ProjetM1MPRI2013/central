#include "chat_event.h"
#include "assert.h"


ChatEvent::ChatEvent() {
	data = "";
}
ChatEvent::ChatEvent(const ChatEvent& tobecopied) {
  this->data = std::string(tobecopied.data);
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
