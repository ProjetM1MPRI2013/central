#ifndef STUFFLIST_H
#define STUFFLIST_H

#include "Clickable.h"
#include "Stuff.h"

class Weapon : public Stuff {
 public:
  Weapon(std::string n);
  /**
   * @brief Compute the number of damage .  
   */
  virtual int damage () ;
};

class Bomb : public Stuff {
 public :
  Bomb ();
};

class Knife : public Weapon {
 public : 
  Knife () ;
 private :
  /**
   * @brief The material 0 if it's in plastic, 1 in wood 
   */
  std::string material;
};



class Gun : public Weapon {
 public :
 /**
   * @brief Create a Gun
   * @param max Number of ammunition maximum
   * @param dam Damagemade by a shot
   * @param range Range of the gun
   */
  Gun (int max, int dam, int range) ;
  /**
   * @brief Number of ammunition in the gun   
   */
  int nAmmunition;
  /**
   * @brief Number of ammunition maximum   
   */
  int nMax;
  /**
   * @brief range of the gyn   
   */
  int range;
 private: 
  /**
   * @brief damage   
   */
  int ndamage ;
  
};

  class Ammunition : public Stuff {
 public :
 /**
   * @brief Create a pack of ammunition
   * @param n Number of ammunitions in the pack 
  Ammunition (int n) ;
  /**
   * @brief number Number of ammunition in the pack   
   */
  int number;
};

#endif
