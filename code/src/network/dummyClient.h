#ifndef DUMMYCLIENT_H
#define DUMMYCLIENT_H

#include "client.h"
#include "dummyServer.h"

using namespace std ;

/**
 * @brief The DummyClient class
 * Class used for debug. Provides an implementation of the
 * Client interface. Will just copy the events, and not use
 * the network, nor carry out any serialization
 */


class DummyClient : public Client{

    friend DummyServer::~DummyServer() ;

public:
    /**
     * @brief DummyClient
     * Creates a new Client, connected to the server.
     * All events sent will be copied to the server
     * The server will copy any update to the client
     * @param server : the server the Client will connect to
     */
    DummyClient(DummyServer& server);

    /**
     * @brief addUpdate
     * @param gu : the game update to add to the recieved
     * updates.
     */
    void addUpdate(GameUpdate& gu) ;

protected :
    /**
     * protected destructor : the client will be
     * destroyed either when the server is destroyed,
     * or by call to shutdown (not implemented for now).
     */
    virtual ~DummyClient() ;

    /**
     * @brief recieved_updates
     * Stores the updates recieved from now.
     * Will be replaced by an empty vector when
     * recieved_updates is called.
     */
    vector<GameUpdate>* recieved_updates;
    /**
     * @brief server
     * The server this client is connected to.
     */
    DummyServer* server ;

    /*
     * Methods inherited from the server interface
     */

public :

    virtual void sendEvent(Event& event) ;

    virtual vector<GameUpdate>& recieveUpdates() ;

    virtual vector<NetEvent>& recieveNetEvents() ;
};

#endif // DUMMYCLIENT_H
