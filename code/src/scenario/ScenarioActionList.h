#ifndef SCENARIOACTIONLIST_H
#define SCENARIOACTIONLIST_H

#include "simulation/npc.h"
#include "generation/tile.h"
#include "ScenarioAction.h"
#include "simulation/player.h"
#include "scenario/ActionsTerro.h"
#include <iostream>
#include <cerrno>

enum NewMov {P_RIGHT, P_LEFT, P_UP, P_DOWN, R_RIGHT, R_LEFT, R_UP, R_DOWN};

/**
 * @brief The player changes of direction.
 */
class ChangeDirection: public ScenarioAction {
 public:
  int playerID;
  
  /**
   * @brief The new direction of the player
   */
  NewMov newMovement;

  ChangeDirection(int id, NewMov mov, Simulation* s);

  virtual void run();
};

class AddCops: public ScenarioAction {
 public:
  int number;
  float x;
  float y;
  AddCops (int n, float xx, float yy,Simulation* s);
  virtual void run ();
};



class AddCams: public ScenarioAction {
 public:
  int number;
  float x;
  float y;
  AddCams(int number,float x,float y,Simulation* s);
  virtual void run ();
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

  Explosion (Tile* t,int p,Simulation* s);

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

  KillNPC(NPC* t,Simulation* s);

  virtual void run ();
};

class DropItem : public ScenarioAction{
 public :
  Stuff* stuff;
  int playerID;
  /**
   *@param stuffO : item to drop
   *@param id : id of the player
   */
  DropItem(Stuff* stuffO,int id, Simulation* s);
  virtual void run ();
};
#endif
