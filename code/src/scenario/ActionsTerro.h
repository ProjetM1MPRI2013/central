/**
   @author: Remy, Adrien K.
 */


#ifndef ACTIONTERRO_H
#define ACTIONTERRO_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>

#include "Clickable.h"
#include "Action.h"
#include "Stuff.h"
#include "StuffList.h"
#include "simulation/npc.h"
#include "generation/tile.h"
#include "Actions.h"
#include "ScenarioActionList.h"
#include "NewMov.h"
#include "tile.h"
#include "position.h"
#include "npc.h"



void newMovement (NewMov n, Simulation* s);


class Drop : public Action{
 public : 
   /**
   * @brief Create a way to drop one stuff
   * @param stuff the stuff to drop
   */
  Drop  (int stuffID, LocalState* s);
  Drop(const Drop& d);
   /**
   * @brief the stuff to drop
   */
  int stuffID;
  int playerID;

  bool isActionPossible ();
  void doAction ();
  void addPendingActions(GlobalState* hs);

  virtual AbstractMessage* copy();

protected :
  //Serialization
  Drop() {}

  SIMPLE_MESSAGE(DROP, Action, stuffID, playerID)
};

BOOST_CLASS_EXPORT_KEY(Drop)

class Attack : public Action {
 public : 
   /**
   * @brief Create an Attack
   * @param weapon the weapon used
   * @param victim the victim
   */
  Attack (int weaponID, NPC* victim, LocalState* s);
  Attack (const Attack& a);
   /**
   * @brief the weapon
   */
  int weaponID;
   /**
   * @brief the victim
   */
  NPC* vict;

  bool isActionPossible ();
  void doAction ();
  void addPendingActions(GlobalState* hs);

  virtual AbstractMessage* copy();

private :
  //Serialization
  Attack() {}

  SIMPLE_MESSAGE(Attack, Action, weaponID)
};

BOOST_CLASS_EXPORT_KEY(Attack)


class Plant : public Action {
 public : 
   /**
   * @brief Create an action to plant a bomb
   * @param bomb the bomb used
   * @param zone the zone where the bomb will be planted 
   */
  Plant (int bombID ,Tile* zone, LocalState* s);
  Plant (const Plant&);
   /**
   * @brief the bomb
   */
  int bombID;
   /**
   * @brief the zone
   */
  Tile* z;

  bool isActionPossible ();
  void doAction ();
  void addPendingActions(GlobalState* hs);

  virtual AbstractMessage* copy();

private :
  //Serialization
  Plant(){}

  SIMPLE_MESSAGE(Plant, Action, bombID)
};

BOOST_CLASS_EXPORT_KEY(Plant)

class Reload : public Action {
 public : 
   /**
   * @brief Create an action to reload a gun
   * @param gun the gun to reload
   * @param Ammunition the pack of ammunition used
   */
  Reload (int gunID, int ammunitionID, LocalState* s);
  Reload(const Reload&);
   /**
   * @brief the gun
   */
  int gunID;
   /**
   * @brief the pack of ammunition
   */
  int ammunitionID;
 
  bool isActionPossible ();
  void doAction ();
  void addPendingActions(GlobalState* hs);

  virtual AbstractMessage* copy();

private :
  //Serialization

  Reload() {}

  SIMPLE_MESSAGE(Reload, Action, gunID, ammunitionID)
};

BOOST_CLASS_EXPORT_KEY(Reload)

#endif
