#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include "serverInfo.h"
#include "clientInfo.h"

class Server {

public : 
  /*
    Creates a server from informations provided by the user. The information
    contain the port number the server will be using, and possibly other 
    parameters. 
    The server will be started and will immediately accept new clients until 
    it is told to start the game.
   */
  Server(ServerInfo s_info){} ;

  /*
    Will send new opdates to all the clients connected to the server. 
    What will effectively be sent to each client will be evaluated, and only
    relevant data will be sent to the network.
    There is no guarantee that the data will effectively be delivered (using 
    UDP protocol).
   */
  virtual void sendUpdate(GameState game_state) = 0 ;

  /*
    Same as previously except that the server will send an update only to 
    the client specified.
   */
  virtual void sendUpdate(GameState game_state, ClientInfo c_info) = 0 ;

  /*
    Returns an array containing all the events recieved from the clients.
    If none has been recieved, the function returns immediately with an 
    empty vector.
   */
  virtual std::vector<Event>& recieveEvents() = 0;

} ;

#endif
