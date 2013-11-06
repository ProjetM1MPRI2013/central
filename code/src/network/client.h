
#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <string>
#include "clientInfo.h"


//temporary declaration of class used by clients
class GameState ;
class GameUpdate ;
class Event ;

/**
 * @brief The Client class
 * Interface to describe methods provided by communications handler on the client side.
 * Other functions will probably be added after.
 * For now it allows to recieve updates from the server, and send events to the server.
 * The connexion is initiated when the object is created.
 * @see Network::createClient to get an instance of this class.
 */


class Client {
 public :
    /**
     * Sends an event to the server in a reliable way. The event will be recieved
     * by the server, the network package is in charge to ensure its delivery
     */
  virtual void sendEvent(Event event) = 0 ;

    /**
     * Returns a vector containing all the Updates from the server. These updates
     * will be used to compute the local state on the client machine.
     * If no update has been recieved yet, the function returns immediately,
     * and the vector will be empty
     */
  virtual std::vector<GameUpdate>& recieveUpdates() = 0 ;

} ;

#endif
