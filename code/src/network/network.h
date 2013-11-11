#ifndef NETWORK_H
#define NETWORK_H

#include "server.h"
#include "client.h"


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
    static Server& createDummyServer() ;

    /**
     * @brief createDummyClient
     * creates a dummy client connected to the server passed in argument. If
     * the server is not an instance of DummyServer, it will result in undefined
     * behavior.
     * Data passed are simply copied, no serialization carried out.
     * @param server The server to communicate with
     * @return The newly created client.
     */
    static Client& createDummyClient(Server & server) ;

};


#endif // NETWORK_H
