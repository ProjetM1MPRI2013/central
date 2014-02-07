/**
   @author: Adrien K.
 */


#ifndef SCENARIOACTIONLIST_H
#define SCENARIOACTIONLIST_H

#include "simulation/npc.h"
#include "generation/tile.h"
#include "ScenarioAction.h"
#include "scenario/ActionsTerro.h"
#include "NewMov.h"
#include <iostream>
#include <cerrno>


class Couple {
public:
  int x;
  int y;
  Couple (int x, int y);
};

Couple* directionToInt(Direction a);
Couple* newMovToInt(NewMov a);
Direction intToDirection(Couple* a);

/**
 * @brief The player changes of direction.
 */
class ChangeDirection: public ScenarioAction {
 public:
  int playerID;
  
  /**
   * @brief The new direction of the player
   */
  Direction newDirection;
  int timeStamp;

  ChangeDirection(int id, Direction direction, int ts, Simulation* s);
  ChangeDirection(const ChangeDirection&);

  virtual void run();

  //AbstractMessage functions
  virtual AbstractMessage* copy();
protected :
  //Serialization
  ChangeDirection() {}

  SIMPLE_MESSAGE(ChangeDirection, ScenarioAction, playerID, newDirection, timeStamp)

};


class AddCops: public ScenarioAction {
 public:
  int number;
  float x;
  float y;
  AddCops (int n, float xx, float yy,Simulation* s);
  AddCops (const AddCops&);

  virtual void run ();

  //AbstractMessage functions
  virtual AbstractMessage* copy();

protected :
  //Serialization
  AddCops(){}

  SIMPLE_MESSAGE(AddCops, ScenarioAction, number, x, y)
};


class AddCams: public ScenarioAction {
 public:
  int number;
  float x;
  float y;
  AddCams(int number,float x,float y,Simulation* s);
  AddCams(const AddCams&);

  virtual void run ();

  virtual AbstractMessage* copy();

private :
  //Serialization
  AddCams(){}

  SIMPLE_MESSAGE(AddCams, ScenarioAction, number, x, y)
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
  Explosion (const Explosion&);

  virtual void run ();

  virtual AbstractMessage* copy();

private :
  //Serialization
  Explosion(){}

  SIMPLE_MESSAGE(Explosion, ScenarioAction, power)
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
  KillNPC(const KillNPC&);

  virtual void run ();

  //AbstractMessage functions
  virtual AbstractMessage* copy();

private :
  //Serialization
  KillNPC(){}

  SIMPLE_MESSAGE(KillNPC, ScenarioAction)

};

class DropItem : public ScenarioAction{
 public :
  int stuffID;
  int playerID;

  /**
   *@param stuffO : item to drop
   *@param id : id of the player
   */
  DropItem(int stuffID, int id, Simulation* s);
  DropItem (const DropItem&);
  
  virtual void run ();

  //AbstractMessage functions
  virtual AbstractMessage* copy();

private :
  //Serialization
  DropItem(){}

  SIMPLE_MESSAGE(DropItem, ScenarioAction, stuffID, playerID)
};


#endif
