#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include <string>
#include <assert.h>

/**
 * @brief The AbstractMessage class
 * This calss defines an interface which messages sent over
 * the network must respect.
 *
 * All the methods of this class should be overridden in children
 * classes (including static ones). Any class that implements this
 * interface can be used to call receiveMessages<MsgType>() and
 * sendMessage<MsgType>(message).
 *
 * For now only classes directly diriving from the AbstractMessage
 * class can be sent over the network. For example, you should not
 * try to do something like :
 *     AbstractMessage
 *           |
 *       MessageBase
 *           |
 *      MessageChild
 *
 * Here, you should not use the MessageChild class to send data
 * on the network. If you still want to use inheritance, tell me,
 * some modifications will be required.
 */
class AbstractMessage {
public :
  /**
   * @brief getMsgType
   * @return a string object representing the Class of a message
   *
   * Every class extending the AbstractMessageInterface must
   * provide their own implementation of the getMsgType method.
   */
  static std::string getMsgType() { assert(false) ;}

  /**
   * @brief toString : serialize the object.
   * @return The string representation of this message
   */
  virtual std::string & toString() =0 ;

  /**
   * @brief fromString : function used for deserialisation
   * @param msg : the string representation of the message
   * @return The message created from its representation
   * All classes inherited from AbstractMessage should implement
   * the function fromString with the signature :
   * static MsgType * fromString(std::string)
   */
  static AbstractMessage * fromString(std::string& msg){ assert(false);}

  /**
   * @brief copy : copy the message
   * @return a new instance of the message, containing the same data
   */
  virtual AbstractMessage* copy() =0 ;

};

#endif // ABSTRACTMESSAGE_H
