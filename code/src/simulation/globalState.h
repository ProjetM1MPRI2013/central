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

class GlobalState /*: public Simulation*/{
 public :
  /**
   * @brief GlobalState
   * @param _seed : a seed used for map creating
   * Default constructor
   */
  GlobalState(std::string _seed);
} ;
#endif
