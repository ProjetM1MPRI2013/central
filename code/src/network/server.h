#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include "serverInfo.h"
#include "clientInfo.h"
#include "netEvent.h"
#include "gameState.h"
#include "event.h"

class Server {

public : 

  /**
   * Will send new opdates to all the clients connected to the server.
   * What will effectively be sent to each client will be evaluated, and only
   * relevant data will be sent to the network.
   * There is no guarantee that the data will effectively be delivered (using
   * UDP protocol).
   */
  virtual void sendUpdate(GameState &game_state) = 0 ;

  /**
   * Returns an array containing all the events recieved from the clients.
   * If none has been recieved, the function returns immediately with an
   * empty vector.
   */
  virtual std::vector<Event>& receiveEvents() = 0;

  /**
   * @brief recieveNetEvents
   * @return A vector containing events related to connexion messages. (A new
   * player joined, server unreachable ...). Empty vector if none has been
   * recieved yet.
   */
  virtual std::vector<NetEvent>& receiveNetEvents() = 0 ;

} ;

#endif
