#include "StuffList.h"



Weapon::Weapon (std::string n): Stuff(n) {
   this->actionsPossible.push_back("Attack");
};

int Weapon::getRange () {return 0;};
int Weapon::getDamage () {return 0;};

Bomb::Bomb () : Stuff("Bomb") {
  this->actionsPossible.push_back("Plant");
  this->power = 1;
};


Knife::Knife () : Weapon ("Knife") {
};


int Knife::getRange () {return 1;};
int Knife::getDamage () {return 1;};

Gun::Gun(int max, int dam,int ran) : Weapon ("Gun") {
  ammunitionLoaded = max;
  ammunitionMax = max;
  this->range = ran;
  this->damage = dam;
  this->actionsPossible.push_back("Reload");
};


int Gun::getRange () {return (this->range);};
int Gun::getDamage () {return (this->damage);};



Ammunition::Ammunition (int n) : Stuff("Ammunition") {
  number=n;
};

