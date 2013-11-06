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
     * @param s_info : informations provided to start the server
     * @return a newly created server.
     * Creates a server from informations provided by the user. The informations
     * provided contain the port number the server will be using, and possibly other
     * parameters.
     * This will start the server immediately, and start listening for events from the
     * users
     */
    static Server& createServer(ServerInfo s_info) ;

    /**
     * @brief createClient
     * @param c_info : informations provided to start the client
     * @return a newly created client
     * Creates a Client using the informations provided by the user (ie :Address of the server).
     * If not set by the client, the local internet address used by the client
     * will be filled in the corresponding fields of c_info.
     * The client will be immediately operationnal to communicate with the server.
     */
    static Client& createClient(ClientInfo c_info) ;

};


#endif // NETWORK_H
