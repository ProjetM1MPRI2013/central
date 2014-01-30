#ifndef CHATEVENT_H
#define CHATEVENT_H
#include "../network/abstractMessage.h"

class ChatEvent : public AbstractMessage{
public:
	static const std::string MSG_TYPE ;
	  /**
	   * @brief ChatEvent : creates a new ChatEvent instance.
	   * The Data is set to a empty string by Default
	   */
	ChatEvent();
	ChatEvent(const ChatEvent&);
	  /**
	   * @brief toString : unimplemented yet
	   */
	virtual std::string toString() ;
	  /*
	   * Methods inherited from the AbstractMessage interface
	   */

	static std::string getMsgType() ;
		/**
	   * @brief toString : unimplemented yet
	   */
	static ChatEvent * fromString(std::string& msg) ;
	/**
	 * @brief copy : Copy
	 */
	virtual ChatEvent* copy() ;
	/**
	 * @brief setData : SetData
	 * @param string
	 */
	void setData(std::string);
	/**
	 * @brief getData : GetDat
	 * @return : The Data of the Chat message
	 */
	std::string getData();
protected :
	/**
	 * @bried data : the data that is attached to the message.
	 */
	  std::string data ;
};

#endif // NETEVENT_H
