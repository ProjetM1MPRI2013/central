#include "StuffList.h"



Weapon::Weapon (std::string n): Stuff(n) {
	std::list<SoN> l_attack ;
	l_attack.push_back(SON_NPC);
	ActionType* A_attack = new ActionType  ("attack",l_attack);
	this->ActionTypePossible.push_back(A_attack);
};

float Weapon::getRange () {return 0;};
int Weapon::getDamage () {return 0;};



Bomb::Bomb (int p) : Stuff("Bomb") {
	std::list<SoN> l_plant ;;
	ActionType* A_plant = new ActionType  ("plant",l_plant);
	this->ActionTypePossible.push_back(A_plant);
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
  std::list<SoN> l_reload ;
  l_reload.push_back(SON_STUFF);
  ActionType* A_reload = new ActionType  ("reload",l_reload);
  this->ActionTypePossible.push_back(A_reload);
};


float Gun::getRange () {return (this->range);};
int Gun::getDamage () {return (this->damage);};


Ammunition::Ammunition (int n) : Stuff("Ammunition") {
  number=n;
};

