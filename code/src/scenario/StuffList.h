#ifndef STUFFLIST_H
#define STUFFLIST_H

#include "Clickable.h"
#include "Stuff.h"
#include <list>

class Weapon : public Stuff {
 public:
  Weapon(std::string n);
  /**
   * @brief Compute the number of damage .  
   */
  virtual int getDamage () ;
  /**
   * @brief Compute the range of the weapon .  
   */
  virtual int getRange () ;
};

class Bomb : public Stuff {
 public :
  Bomb ();
 private:
  int power;
};

class Knife : public Weapon {
 public : 
  Knife () ;
  int getDamage();
  int getRange();
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
  int ammunitionLoaded;
  /**
   * @brief Number of ammunition maximum   
   */
  int ammunitionMax;

  int getDamage();
  int getRange();

 private: 
  /**
   * @brief damage of the gun
   */
  int damage ;
  /**
   * @brief range of the gun   
   */
  int range;
  
};

class Ammunition : public Stuff {
 public :
   /**
   * @brief number Number of ammunition in the pack   
   */
  int number;
  Ammunition (int n);
};

#endif
