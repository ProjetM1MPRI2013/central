/**
  *@author Denys KANUNIKOV,
  */
#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#include "player.h"
#include "generation1.h"
#include "simulation.h"
class Tile; // forward declaration
class Player;


/**
 * @brief The Global State Class
 * Interface to access the global game state
 */

class GlobalState : public Simulation{
 public :
  /**
   * @brief GlobalState
   * @param _seed : a seed used for map creating
   * Default constructor
   */
  
  /* Never used
  GlobalState(std::string _seed, std::vector<Player *> _players);
  */

  GlobalState(Geography* map,int nbPlayers,int id);

  void setServer(Server*);

  void run(sf::Time dt);

private:

} ;
#endif
