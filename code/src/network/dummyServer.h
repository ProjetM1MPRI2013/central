#ifndef DUMMYSERVER_H
#define DUMMYSERVER_H

#include "server.h"

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
     * @brief addEvent
     * Adds an event to the recieved_events
     * @param event : the event to add.
     */
    void addEvent(Event& event) ;

private :
    /**
     * @brief clients : all the clients connected to
     * this server
     */
    std::vector<DummyClient*> clients ;

    /**
     * @brief events : all the events recieved from now.
     * Will be reset when recieveEvents() is called.
     */
    std::vector<Event> *events ;

    /*
     *Methods inherited from Client
     */

public :

  virtual void sendUpdate(GameState &game_state) ;

  virtual std::vector<Event>& receiveEvents() ;

  virtual std::vector<NetEvent>& receiveNetEvents() ;

};

#endif // DUMMYSERVER_H
