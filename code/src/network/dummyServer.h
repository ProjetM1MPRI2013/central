#ifndef DUMMYSERVER_H
#define DUMMYSERVER_H

#include <map>
#include <list>
#include <mutex>

#include "server.h"
#include "netEvent.h"

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
     * The server gains ownership of the message passed in argument.
     */
    void addMessage(AbstractMessage* msg, std::string msgType, DummyClient *cli) ;

private :
    /**
     * @brief clients : all the clients connected to
     * this server
     */
    std::list<DummyClient*> clients ;

    /**
     * @brief players : associates to each player ID the client it is associated to.
     */
    std::map<int, DummyClient *> players ;

    typedef std::map<std::string, std::vector<AbstractMessage*>* > MapType ;
    /**
     * @brief received_messages : used to store all the messages received from now.
     * Associates to each type of message a vector containing all the messages
     * received.
     */
    MapType received_messages ;

    /**
     * @brief lock : to prevent concurrent access to the structure
     */
    std::mutex lock ;

protected :

    /**
     * @brief handle_netEvent : handles the given NetEvent when it is received. Special operations can be carried on NetEvents
     * when they are received
     * @see NetEvent for details
     * @param event
     * @return true if the event should be passed to the user. False otherwise.
     */
    virtual bool handle_netEvent(NetEvent& event, DummyClient *client) ;

    /*
     *Methods inherited from Server
     */
    virtual void send_message(AbstractMessage& msg, bool reliable, std::string msgType, int player =-1) ;

    virtual std::vector<AbstractMessage *> receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) ;

    virtual std::vector<int> getConnectedPlayers() ;

    virtual bool isConnected(int player) ;

public :

    // deprecated
    //virtual void sendUpdate(GameState &game_state) ;

};

#endif // DUMMYSERVER_H
