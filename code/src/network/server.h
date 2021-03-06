#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include <SFML/System/Clock.hpp>

#include "serverInfo.h"
#include "abstractMessage.h"

class GlobalState ;


/**
 * @brief The Server interface.
 * Provides the basic functionnalities for the server.
 * Allows to broadcast/receive events through the network (in a reliable way or not)
 * Also allows to broacast game updates to all the clients.
 * On its creation, the server will wait for external messages. The server will register any client sending a SERV_TRY message
 * as a connected Client, which will be notified when messages are sent usong broadcastMessage.
 * If a client fails to ack a message sent with the reliable option set to true, this client is removed
 * from the list of connected clients, and a CLI_LOST NetEvent is generated on the Server side
 * and broadcasted to all the other clients.
 * @author mheinric
 */
class Server {

public : 

  /**
   * @brief broadcastMessage : broadcasts a message of the given type to all the clients
   * @param msg : the message to send
   * @param reliable : whether the server should wait for an ack or not.
   * The caller retains ownership of the message. The message can be deleted as soon as the
   * function returns.
   */
  template <typename MsgType>
  void broadcastMessage(MsgType& msg, bool reliable = true){
    send_message(msg,reliable,MsgType::getMsgType());
  }

  /**
   * @brief receiveMessages : Receives all the messsages of the given type.
   * @return all the messages received from nom with type MsgType.
   * MsgType should extend the AbstractMessage interface.
   * @see AbstractMessage
   * Will only return messages of the given class. If there are pending messages
   * of a subclass, they won't be transferred by a call to receive on the superclass.
   * For example :
   *       AbstractMessage
   *            |
   *       MessageBase
   *            |
   *       MessageChild
   *
   * A call to receiveMessages<MessageBase>() won't return instances of MessageChild if
   * some have been received.
   * The caller gains ownership of all the messages in the vector.
   */
  template <typename MsgType>
  std::vector<MsgType *> receiveMessages(){
    //function pointer casting ----> not sure it works
    std::vector<AbstractMessage*> result1 = receive_messages(MsgType::getMsgType(),
                                                             (AbstractMessage* (*) (std::string &)) & MsgType::fromString) ;
    std::vector<MsgType*> result2 ;
    for(AbstractMessage* p : result1)
      {
        result2.push_back((MsgType *)p);
      }
    return result2 ;
  }
  /**
   * @brief Sends a message only to the given player.
   * @param msg : The message to send
   * @param player : the ID of the player to send the message to
   * @param reliable : wether or not the server should wait for an ACK.
   * The caller retain ownership of the message passed in argument.
   */
  template <typename MsgType>
  void sendMessage(MsgType& msg, int player, bool reliable = true){
    send_message(msg,reliable,MsgType::getMsgType(), player);
  }

  /**
   * @brief getConnectedPlayers :
   * returns a vector with all the players connected to this server. Each element of the
   * vector correspond to a Player Id (getID() form simulation/Player
   * A player is registered as connected when the server receives a NetEvent message with type
   * PLAYER_JOIN, with the data containing the ID of the player that has joined.
   * A player is removed from this server when the server receives or transmit a NetEvent message
   * with type PLAYER_QUIT, with the corresponding ID in the field data.
   * @return a vector containing the ID of all the players that are connected to this server.
   */
  virtual std::vector<int> getConnectedPlayers() = 0 ;

  /**
   * @brief isConnected : checks wether there is a player with the given ID connected to the server.
   * @param player : the ID of the player
   * @return true if the player is connected, false otherwise.
   */
  virtual bool isConnected(int player) = 0 ;


  /**
   * @brief setSimulation : sets the simulation associated with this server instance.
   * @param simu
   * This method should be called before any call to update().
   * Will generate an error Log if it is called more than once on the same server.
   */
  virtual void setSimulation(GlobalState * simu) = 0 ;

  /**
   * @brief update : sends updates of the simulation object associated to this server.
   * Should not be called when the simulation has not already been set. Will generate
   * a warning log otherwise.
   */
  virtual void update(sf::Time dt) = 0 ;



  virtual ~Server() {}



  //only reason for private members in this interface is that templates cannot be
  // declared virtual.
protected :
  /**
   * @brief braodcast_message : (Internal do not use) sends a message to all the clients
   * @param msg : the message to send
   * @param reliable : whether the server should wait for an Ack or not
   * @param msgType : A string describing the type of the message (result of getMsgType())
   * @param player : the player to send the message to. -1 to send the message to all the players
   */
  virtual void send_message(AbstractMessage& msg, bool reliable, std::string msgType, int player = -1) =0 ;

  /**
   * @brief receive_messages : (Internal do not use) receives messages of the given type
   * @param msgType : a string describing the type of the messages to receive (result of getMsgType())
   * @param f : function used for deserialisation
   * @return : a vector containing all the messages of this type received from now.
   */
  virtual std::vector<AbstractMessage * > receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) =0;

} ;

#endif
