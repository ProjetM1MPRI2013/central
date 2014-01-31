#ifndef NETEVENT_H
#define NETEVENT_H

#include "abstractMessage.h"


/**
 * @brief The NetEvent class
 * Class used to communicate between the server and the
 * client.
 *
 * Provides a mean to notify the user about connexion
 * event. Some of these events can be generated by the implementation
 * of the server/client interface. Some other are only generated
 * expicitely by the client.
 * NetEvent will be handled in a particular way both by the client and the server.
 * The particular behaviours are the following :
 *  - SERV_TRY(resp CLI_TRY) will not be passed to the user when they are received. A
 *  - SERV_RESP(resp CLI_RESP) message will be directly answered, the message is then discarded
 *  - PLAYER_JOIN : the content of the message will be used to identify the Player in the future.
 *  - ACK messages are only used internally and shoud not be sent. They are always discarded.
 * @author mheinric
 */

class NetEvent : public AbstractMessage{
public:

  typedef enum Type {

    /**
     * @brief NOT_SET : default value used on creation.
     * No meaning associated
     */
    NOT_SET,

    /**
     * @brief SERV_LOST : message generated when the server does not answer for a long time
     * no data attached
     */
    SERV_LOST = 1,

    /**
     * @brief SERV_TRY : send a message to the server to see if it responds
     * The server answers by a SERV_RESP message
     * no data attached
     */
    SERV_TRY ,

    /**
     * @brief SERV_RESP : server answer to SERV_TRY. Must not be sent manually
     * no data attached
     */
    SERV_RESP ,

    /**
     * @brief CLI_LOST : generated when the client does not respond for a long time
     * no data attached
     */
    CLI_LOST ,

    /**
     * @brief CLI_TRY : tries to contact the client. If it receives the message,
     * the client answers with CLI_RESP
     * no data attached
     */
    CLI_TRY ,

    /**
     * @brief CLI_RESP : client's answer to CLI_TRY. Must not be sent manually
     * no data attached
     */
    CLI_RESP ,

    /**
     * @brief MSG_LOST : message generated when a message could not be delivered.
     * data is the number associated with the message lost
     */
    MSG_LOST ,

    /**
     * @brief PLAYER_JOIN : send this message to notify the server or other players
     * that a player joined the game.
     * data is the id of the player that joined the game.
     * This message is used by the server to determine wich are the players connected to it.
     */
    PLAYER_JOIN ,

    /**
     * @brief PLAYER_QUIT : send this message to notify the server or other players
     * that a player left the game
     * data is the id of the player that left the game.
     * This message is used by the server to determine wich are the players connected to it.
     */
    PLAYER_QUIT ,

    /**
     * @brief SEND_ERROR : generated when an error occured while
     * sending a message
     * data is the number associated with the message
     */
    SEND_ERR ,

    /**
     * @brief RECEIVE_ERR : generated when an error occured when
     * receiving a message.
     * no data attached
     */
    RECEIVE_ERR, 
		
		/**
		 * @brief ACK : sent when a message requires a check that it did arrive
     * at its destination.
     * data is the number of the message to ack.
		 */
		ACK

  } Type ;


  static const std::string MSG_TYPE ;


  /**
   * @brief NetEvent : creates a new NetEvent instance.
   * The type is set to 0 by default. A type of 0 is meant to
   * carry no meaning.
   */
  NetEvent();

  /**
   * @brief NetEvent : creates a new NetEvent with the given type
   */
  NetEvent(Type type) ;

  /**
   * @brief getType
   * @return the type of this message
   */
  NetEvent::Type inline getType() const { return type ;}

  /**
   * @brief setType
   * @param type : the type to set to this message
   */
  virtual inline void setType(NetEvent::Type type){this->type = type ;}


  virtual inline void setData(int data){
    this->data = data ;
  }

  virtual inline int getData() const {
    return data ;
  }



  /*
   * Methods inherited from the AbstractMessage interface
   */
  //static std::string getMsgType() ;
  /**
   * @brief toString : unimplemented yet
   */
  //virtual std::string toString() ;
  /**
   * @brief fromString : unimplemented yet
   */
  //static NetEvent * fromString(const std::string& msg) ;

  virtual NetEvent* copy() ;


protected :
  /**
   * @brief type : the type of this message.
   * The possible types are described in static fields.
   */
  Type type ;

  /**
   * @brief data : the data that is attached to this message.
   * Each message type should define what means the data
   * attached with the message.
   * Some message Type do not require a precise data field, in this case,
   * the field data may contain anything
   */
  int data ;

  SIMPLE_MESSAGE(NetEvent, AbstractMessage, type, data)

};

std::ostream& operator<<(std::ostream& os, const NetEvent& obj) ;

BOOST_CLASS_EXPORT_KEY(NetEvent)
#endif // NETEVENT_H
