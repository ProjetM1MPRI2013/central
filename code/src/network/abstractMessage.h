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
 */
class AbstractMessage {
public :
  /**
   * @brief getMsgType
   * @return a string object representing the Class of a message
   *
   * Every class extending the AbstractMessageInterface must
   * provide their own implementation of the getMsgType method.
   * The returned string must be exactly 8 characters long.
   * (it will be sent over the network, so a fixed size is required).
   */
  static std::string getMsgType() { assert(false) ;}

  /**
   * @brief toString : serialize the object.
   * @return The string representation of this message
   */
  virtual std::string toString() =0 ;

  /**
   * @brief fromString : function used for deserialisation
   * @param msg : the string representation of the message
   * @return The message created from its representation
   * All classes inherited from AbstractMessage should implement
   * the function fromString with the signature :
   * static MsgType * fromString(std::string)
   */
  static AbstractMessage * fromString(const std::string& msg){ assert(false);}

  /**
   * @brief copy : copy the message
   * @return a new instance of the message, containing the same data
   */
  virtual AbstractMessage* copy() =0 ;

  virtual ~AbstractMessage(){ }

};

#endif // ABSTRACTMESSAGE_H
