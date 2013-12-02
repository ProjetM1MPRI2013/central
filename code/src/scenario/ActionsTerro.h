#ifndef ACTIONTERRO_H
#define ACTIONTERRO_H

#include "Clickable.h"
#include "Action.h"
#include "Stuff.h"
#include "StuffList.h"
#include "../simulation/npc.h"
#include "../generation/tile.h"

class Drop : public Action{
 public : 
   /**
   * @brief Create a way to drop one stuff
   * @param stuff the stuff to drop
   */
  Drop  (Stuff* stuff);
   /**
   * @brief the stuff to drop
   */
  Stuff* stu;
};

class Attack : public Action {
 public : 
   /**
   * @brief Create an Attack
   * @param weapon the weapon used
   * @param victim the victim
   */
  Attack (Weapon* weapon,NPC* victim);
   /**
   * @brief the weapon
   */
  Weapon* weap;
   /**
   * @brief the victim
   */
  NPC* vict;
};



class Plant : public Action {
 public : 
   /**
   * @brief Create an action to plant a bomb
   * @param bomb the bomb used
   * @param zone the zone where the bomb will be planted 
   */
  Plant (Bomb bomb ,Tile zone);
   /**
   * @brief the bomb
   */
  Bomb bo;
   /**
   * @brief the zone
   */
  Tile z;
};


class Reload : public Action {
 public : 
   /**
   * @brief Create an action to reload a gun
   * @param gun the gun to reload
   * @param Ammunition the pack of ammunition used
   */
  Reload (Gun gun,Ammunition ammunition);
   /**
   * @brief the gun
   */
  Gun g;
   /**
   * @brief the pack of ammunition
   */
  Ammunition ammu;
 
};









#endif
