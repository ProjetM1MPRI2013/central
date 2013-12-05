#ifndef UPDATEGENERATOR_H
#define UPDATEGENERATOR_H
#include "server.h"
#include "gameUpdate.h"
class Simulation;
#include "simulation/simulation.h"

/**
 * @brief The UpdateGenerator class : class used to generate updates on the Server side.
 * Call the update() method to send updates to all the clients.
 */
class UpdateGenerator
{
public:

  /**
   * @brief UpdateGenerator : creates a new instance responsible of the synchronisation of the given global state, using the
   * given server as a mean of communication.
   * @param globalState : the global state that will be synced over the network
   * @param server : the server used for communication
   */
  UpdateGenerator(Simulation& globalState, Server& server);

  /**
   * @brief update : A call to this method will generate the gameUpdates for all the Clients, and will
   * send them over the network
   */
  void update() ;

private :
  Simulation* globalState ;
  Server* server ;

  /**
   * @brief generateUpdate : generates the update to be sent to the given player
   * @param player : the player the update will be sent to
   * @return the generated update
   */
  GameUpdate* generateUpdate(Player& player) ;
};

#endif // UPDATEGENERATOR_H
