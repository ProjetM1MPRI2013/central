#ifndef SCENARIOACTIONLIST_H
#define SCENARIOACTIONLIST_H

#include "simulation/npc.h"
#include "generation/tile.h"
#include "ScenarioAction.h"
#include "simulation/player.h"
#include "scenario/ActionsTerro.h"
#include "NewMov.h"
#include <iostream>
#include <cerrno>

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
  ChangeDirection(const ChangeDirection&);

  virtual void run();

  //AbstractMessage functions
  //virtual std::string & toString();
  //static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();
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
  //virtual std::string & toString();
  //static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();
};



class AddCams: public ScenarioAction {
 public:
  int number;
  float x;
  float y;
  AddCams(int number,float x,float y,Simulation* s);
  AddCams(const AddCams&);

  virtual void run ();

  //AbstractMessage functions
  //virtual std::string & toString();
  //static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();
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

  //AbstractMessage functions
  //virtual std::string & toString();
  //static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();
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
  //virtual std::string & toString();
  //static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();
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
  DropItem (const DropItem&);
  
  virtual void run ();

  //AbstractMessage functions
  //virtual std::string & toString();
  //static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();
};

#endif
