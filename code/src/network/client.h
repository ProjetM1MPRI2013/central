
#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <string>
#include "clientInfo.h"
#include "abstractMessage.h"

/**
 * @brief The Client class
 * Interface to describe methods provided by communications handler on the client side.
 * It provides methods to send and receive events over the network.
 * This class does not verify automatically that the server is effectively reacheable.
 * However, if it fails to deliver a message for which a safe delivery was required,
 * it will notify the user through a NetEvent message.
 * These connexion messages will be available through the call receiveMessages<NetEvent>().
 *
 * @see NetEvent for details.
 * @see Network::createClient to get an instance of this class.
 */
class Client {
public :
  /**
   * @brief sendMessage : used to send messages across the Network.
   * @param msg : the message to send.
   * @param reliable : whether the network implementation should check for
   * correct delivery or not.
   *
   * call 'sendMessage<MsgType>(message)' to send a message of type
   * MsgType over the network.
   *
   * The class MsgType should extend the AbstractMessage insterface.
   * In particular, the getMsgType function will be used to determine the
   * type of a recieved message. Thus, two different classes should not
   * return the same value (except if they are serializable compatible).
   *
   * Warning : inheritance is not supported. ie :
   *    AbstractMessage
   *           |
   *      MessageBase
   *           |
   *      MessageChild
   *
   * Then you should not try to send messages of the
   * MessageChild class. If you need to, tell me, some changes might be required
   * in the AbstractMessage interface.
   */
  template<typename MsgType>
  void sendMessage(MsgType& msg, bool reliable = true){
    send_message(msg,reliable, MsgType::getMsgType());
  }

  /**
   * @brief recieveMessages : Recieves messages of a given type.
   * @return A vector containing all the recieved messages of the
   * given type.
   *
   * call 'receiveMessages<MsgType>()' to get all received messages of
   * type MsgType.
   *
   * The same remark as sendMessage concerning inheritance holds.
   */
  template<typename MsgType>
  std::vector<MsgType * > & receiveMessages(){
    //function pointer casting : not sure it works
    return (std::vector<MsgType *> &) receive_messages(MsgType::getMsgType(), (AbstractMessage* (*) (std::string &)) &MsgType::fromString) ;
  }

  // The only reason for private members in this interface is that
  // templates cannot be declared virtual.

  virtual ~Client(){}
protected :
  /**
   * @brief send_message : (Internal do not use) Sends a message with the type given as a parameter.
   * @param msg : the message to send
   * @param reliable : whether an ACK should be sent by the reciever or not
   * @param msgType : The type of the message (result of getMsgType)
   */
  virtual void send_message(AbstractMessage& msg, bool reliable, std::string msgType ) =0 ;

  /**
   * @brief receive_messages : (Internal do not use) receives messages of the given type
   * @param msgType : the type of the message to receive (result from getMsgType)
   * @param f : function used for deserialisation.
   * @return All the messages of the given type received from now.
   */
  virtual std::vector<AbstractMessage *>& receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) = 0 ;

} ;

#endif
