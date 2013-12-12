#include "StuffList.h"



Weapon::Weapon (std::string n): Stuff(n) {
  this->actionsPossible.push_back(Actions::ATTACK);
};

float Weapon::getRange () {return 0;};
int Weapon::getDamage () {return 0;};


Bomb::Bomb (int p) : Stuff("Bomb") {
  this->actionsPossible.push_back(PLANT);
  this->power = p;
};

int Bomb::getPower() {return this->power;};

Knife::Knife () : Weapon ("Knife") {
};


float Knife::getRange () {return 1;};
int Knife::getDamage () {return 1;};

Gun::Gun(int max, int dam,float ran) : Weapon ("Gun") {
  ammunitionLoaded = max;
  ammunitionMax = max;
  this->range = ran;
  this->damage = dam;
  this->actionsPossible.push_back(RELOAD);
};


float Gun::getRange () {return (this->range);};
int Gun::getDamage () {return (this->damage);};


Ammunition::Ammunition (int n) : Stuff("Ammunition") {
  number=n;
};

