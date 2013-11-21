#ifndef CHATEVENT_H
#define CHATEVENT_H
#include "../network/abstractMessage.h"

class ChatEvent : public AbstractMessage{
public:
	static const std::string MSG_TYPE ;
	ChatEvent();
	virtual std::string & toString() ;
	static std::string getMsgType() ;
	static ChatEvent * fromString(std::string& msg) ;
	virtual ChatEvent* copy() ;
	void setData(std::string);
	std::string getData();
protected :
	  std::string data ;
};

#endif // NETEVENT_H
