#ifndef NETWORK_H
#define NETWORK_H

#include "server.h"
#include "client.h"
class UpdateGenerator;
#include "updateGenerator.h"
#include "localStateUpdater.h"
#include "simulation/simulation.h"
#include "simulation/localState.h"


/**
 * @brief The Network class
 * class used to creates instances of the Client and Server.
 */

class Network {

public :
    /**
     * @breif createServer
     * Creates a server from informations provided by the user. The informations
     * provided contain the port number the server will be using, and possibly other
     * parameters.
     * This will start the server immediately, and start listening for events from the
     * users
     * @param s_info : informations provided to start the server
     * @return a newly created server.
     */
    static Server& createServer(ServerInfo s_info) ;

    /**
     * @brief createClient
     * Creates a Client using the informations provided by the user (ie :Address of the server).
     * If not set by the client, the local internet address used by the client
     * will be filled in the corresponding fields of c_info.
     * The client will be immediately operationnal to communicate with the server.
     * At its creation, the client sends a SERV_TRY event to the server.
     * If the Server responds, it will generate a SERV_RESP event on the client side.
     * otherwise, it will genereate a SERV_LOST event.
     * @param c_info : informations provided to start the client
     * @return a newly created client
     */
    static Client& createClient(ClientInfo c_info) ;

    /**
     * @brief createDummyServer
     * Creates an instance of a Server Class wich does not uses network (used for test).
     * No serialization is carried out. Only hard copy of the data passed.
     * @return An instance of the Server Class.
     */
    static Server* createDummyServer() ;

    /**
     * @brief createDummyClient
     * creates a dummy client connected to the server passed in argument. If
     * the server is not an instance of DummyServer, it will result in undefined
     * behavior.
     * Data passed are simply copied, no serialization carried out.
     * At its creation, the client sends a SERV_TRY event to the server.
     * If the Server responds, it will generate a SERV_RESP event on the client side.
     * otherwise, it will genereate a SERV_LOST event.
     * @param server The server to communicate with
     * @return The newly created client.
     */
    static Client* createDummyClient(Server * server) ;


    /**
     * @brief createUpdater : creates a new updater in charge of sending game updates over the network
     * The instance returned will generate updates for all the players connected to the server through the
     * server
     * @param globalState : the global state to synchronize with all the players
     * @param server : will be used to send the messages
     * @return A new updater in charge of synchronizing the global state.
     */
    static UpdateGenerator& createUpdater(Simulation& globalState, Server& server) ;

    /**
     * @brief createUpdater : creates a new updater in charge of receiving and applying updates received from the
     * server. The instance returned will handle received updates through its update method
     * @param localState : the local state that must be synchronized
     * @param client : the object used for communication
     * @return A new updater in charge of synchronizing the local state through the network.
     */
    static LocalStateUpdater& createUpdater(LocalState& localState, Client& client) ;

};


#endif // NETWORK_H
