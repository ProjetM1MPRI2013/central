#ifndef SCENARIOACTIONLIST_H
#define SCENARIOACTIONLIST_H

#include "../simulation/npc.h"
#include "../generation/tile.h"
#include "ScenarioAction.h"

/**
 * @brief The player changes of direction.
 */
class ChangeDirection: public ScenarioAction {
 public:
  int playerID;
  
  /**
   * @brief The new direction of the player
   * 0 stop, 1 up, 2 right, 3 down, 4 left 
   */
  int newMovement;

  ChangeDirection(int id, int mov);

  virtual void run();
};


/**
 * @brief Create a new explosion.
 */
class Explosion: public ScenarioAction {
 public:
  /**
   * @brief The initial location of the explosion
   */
  Tile* location;

  /**
   * The power of the explosion
   */
  int power;

  Explosion (Tile* t,int p);

  virtual void run ();
};


/**
 * @brief Kill a NPC.
 */
class KillNPC: public ScenarioAction {
public:
  /**
   * @brief The NPC targeted
   */
  NPC* target;

  KillNPC(NPC* t);

  virtual void run ();
};

#endif
