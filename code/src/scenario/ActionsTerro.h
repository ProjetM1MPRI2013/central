#ifndef ACTIONTERRO_H
#define ACTIONTERRO_H

#include "Clickable.h"
#include "Action.h"
#include "Stuff.h"
#include "StuffList.h"
#include "simulation/npc.h"
#include "generation/tile.h"
#include "Actions.h"
#include "ScenarioActionList.h"


enum SoN {
	SON_STUFF, SON_NPC
};

void SoNOfActions(Actions a,std::list<SoN> l);

typedef Simulation HostSimulation;

void newMovement (NewMov n);


class Drop : public Action{
 public : 
   /**
   * @brief Create a way to drop one stuff
   * @param stuff the stuff to drop
   */
  Drop  (Stuff* stuff, Simulation* s);
   /**
   * @brief the stuff to drop
   */
  Stuff* stu;
  int playerID;

  bool isActionPossible ();
  void doAction ();
  void addPendingActions(HostSimulation* hs);
};

class Attack : public Action {
 public : 
   /**
   * @brief Create an Attack
   * @param weapon the weapon used
   * @param victim the victim
   */
  Attack (Weapon* weapon, NPC* victim, Simulation* s);
   /**
   * @brief the weapon
   */
  Weapon* weap;
   /**
   * @brief the victim
   */
  NPC* vict;

  bool isActionPossible ();
  void doAction ();
  void addPendingActions(HostSimulation* hs);
};



class Plant : public Action {
 public : 
   /**
   * @brief Create an action to plant a bomb
   * @param bomb the bomb used
   * @param zone the zone where the bomb will be planted 
   */
  Plant (Bomb* bomb ,Tile* zone, Simulation* s);
   /**
   * @brief the bomb
   */
  Bomb* bo;
   /**
   * @brief the zone
   */
  Tile* z;

  bool isActionPossible ();
  void doAction ();
  void addPendingActions(HostSimulation* hs);
};


class Reload : public Action {
 public : 
   /**
   * @brief Create an action to reload a gun
   * @param gun the gun to reload
   * @param Ammunition the pack of ammunition used
   */
  Reload (Gun* gun,Ammunition* ammunition, Simulation* s);
   /**
   * @brief the gun
   */
  Gun* g;
   /**
   * @brief the pack of ammunition
   */
  Ammunition* ammu;
 
  bool isActionPossible ();
  void doAction ();
  void addPendingActions(HostSimulation* hs);
};


#endif
