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
   * @brief GlobalState : default constructor
   * @param map : pointer to the map
   * @param nbPlayers: number of players in the game
   * @param id: id of the current player
   */
  GlobalState(Geography* map,int nbPlayers,int id);

  void setServer(Server*);
  Server* getServer(void);

  void run(sf::Time dt);
private:
    Server *server;
} ;
#endif
