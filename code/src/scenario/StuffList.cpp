#include "StuffList.h"


Weapon::Weapon (std::string n): Stuff(n) {
   this->actionsPossible.push_back("Attack");
};

Bomb::Bomb () : Stuff("Bomb") {
  this->actionsPossible.push_back("Plant");
  
};


Knife::Knife () : Weapon ("Knife") {
  
};

Gun::Gun(int max, int dam) : Weapon ("Gun") {
  nAmmunition = max;
  nMax = max;
  ndamage = dam;
  this->actionsPossible.push_back("Reload");
};


Ammuniton::Ammunition (int n) Stuff("Ammunition") {
  number=n
    };
