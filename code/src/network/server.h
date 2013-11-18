#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include "serverInfo.h"
#include "abstractMessage.h"

/**
 * @brief The GameState class (Temporary, will be replaced by an include when the
 * corresponding class in the simulation module will be defined.
 */
class GameState {} ;

/**
 * @brief The Server interface.
 * Provides the basic functionnalities for the server.
 * Allows to broadcast/receive events through the network (in a reliable way or not)
 * Also allows to broacast game updates to all the clients.
 */
class Server {

public : 

  /**
   * Will send new opdates to all the clients connected to the server.
   * What will effectively be sent to each client will be evaluated, and only
   * relevant data will be sent to the network.
   * There is no guarantee that the data will effectively be delivered (using
   * UDP protocol for the real implementation).
   */
  virtual void sendUpdate(GameState &game_state) = 0 ;

  /**
   * @brief broadcastMessage : broadcasts a message of the given type to all the clients
   * @param msg : the message to send
   * @param reliable : whether the server should wait for an ack or not.
   * @see Client::sendMessage for details
   */
  template <typename MsgType>
  void broadcastMessage(MsgType msg, bool reliable = true){
    broadcast_message(msg,reliable,MsgType::getMsgType());
  }

  /**
   * @brief receiveMessages : Receives all the messsages of the given type.
   * @return all the messages received from nom with type MsgType.
   * MsgType should extend the AbstractMessage interface.
   * @see AbstractMessage
   * @see Client::receiveMessages
   */
  template <typename MsgType>
  std::vector<MsgType *> & receiveMessages(){
    //function pointer casting ----> not sure it works
    return (std::vector<MsgType *> &) receive_messages(MsgType::getMsgType(), (AbstractMessage* (*) (std::string &)) &MsgType::fromString) ;

  }

  //only reason for private members in this interface is that templates cannot be
  // declared virtual.
protected :
  /**
   * @brief braodcast_message : (Internal do not use) sends a message to all the clients
   * @param msg : the message to send
   * @param reliable : whether the server should wait for an Ack or not
   * @param msgType : A string describing the type of the message (result of getMsgType())
   */
  virtual void broadcast_message(AbstractMessage& msg, bool reliable, std::string msgType) =0 ;

  /**
   * @brief receive_messages : (Internal do not use) receives messages of the given type
   * @param msgType : a string describing the type of the messages to receive (result of getMsgType())
   * @param f : function used for deserialisation
   * @return : a vector containing all the messages of this type received from now.
   */
  virtual std::vector<AbstractMessage * >& receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) =0;

} ;

#endif
