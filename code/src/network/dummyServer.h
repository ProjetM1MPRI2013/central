#ifndef DUMMYSERVER_H
#define DUMMYSERVER_H

#include "server.h"
#include <map>

class DummyClient ;


/**
 * @brief The DummyServer class
 *
 * Implements the Server interface trivially.
 * Won't use the network, nor any serialization.
 * Is used with the DummyClient class.
 * @see DummyClient
 */

class DummyServer : public Server {
public:
    /**
     * @brief DummyServer
     * Creates a new DummyServer, with no clients
     */
    DummyServer();

    /**
     * @brief ~DummyServer
     */
    virtual ~DummyServer() ;

    /**
     * @brief addClient
     * Adds a Client to this server. Will transmit all
     * updates to this client as well.
     * @param cli : the Client to add
     */
    void addClient(DummyClient& cli) ;

    /**
     * @brief addMessage : adds a received message to the server with the given type
     * @param msg : the message to add
     * @param msgType : the type of the message
     */
    void addMessage(AbstractMessage& msg, std::string msgType) ;

private :
    /**
     * @brief clients : all the clients connected to
     * this server
     */
    std::vector<DummyClient*> clients ;

    typedef std::map<std::string, std::vector<AbstractMessage*>* > MapType ;
    /**
     * @brief received_messages : used to store all the messages received from now.
     * Associates to each type of message a vector containing all the messages
     * received.
     */
    MapType received_messages ;

protected :
    /*
     *Methods inherited from Server
     */
    virtual void broadcast_message(AbstractMessage& msg, bool reliable, std::string msgType ) ;

    virtual std::vector<AbstractMessage *>& receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) ;

public :

  virtual void sendUpdate(GameState &game_state) ;

};

#endif // DUMMYSERVER_H
