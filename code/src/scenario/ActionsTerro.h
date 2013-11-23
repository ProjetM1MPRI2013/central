#ifndef ACTIONTERRO_H
#define ACTIONTERRO_H

#include "Clickable.h"
#include "Action.h"
#include "Stuff.h"
#include "StuffList.h"

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
  }

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
  int damage ();
}



class Plant : public Action {
 public : 
   /**
   * @brief Create an action to plant a bomb
   * @param bomb the bomb used
   * @param zone the zone where the bomb will be planted 
   * todo : trouver le type de zone
   */
  Plant (Bomb bomb ,Clickable zone);
   /**
   * @brief the bomb
   */
  Bomb bo;
   /**
   * @brief the zone
   */
  Clickable z;
};


class Reload : public Action {
 public : 
   /**
   * @brief Create an action to reload a gun
   * @param gun the gun to reload
   */
  Reload (Gun gun );
   /**
   * @brief the gun
   */
  Gun g; 
};









#endif
