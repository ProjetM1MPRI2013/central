#include "ActionsTerro.h"

/*to ask to denys to implemente */
bool isInThePack(Stuff* stuff) { return true ;};
int distance(NPC* npc) {return 0;};
bool isPlantable (Tile* t) {return true;};


Drop :: Drop (Stuff* s, Simulation* s) : Action ("Drop",s) {
  stu = s;
};

Attack :: Attack (Weapon* weapon,NPC* victim, Simulation* s)  : Action ("Attack",s) {
  vict = victim;
  weap = weapon;
};


Plant :: Plant (Bomb* bomb,Tile* zone, Simulation* s)  : Action ("Plant",s) {
  bo = bomb;
  z = zone;
};

Reload :: Reload (Gun* gun, Ammunition* ammunition, Simulation* s) : Action ("Reload",s) {
  g = gun;
  ammu = ammunition;
};

bool Drop::isActionPossible(){return isInThePack(this->stu);};
void Drop::doAction () {return;};


bool Plant::isActionPossible(){
  return (
	  (isInThePack(this->bo)) 
	  && (isPlantable (this->z))
	  );
};
void Plant::doAction () {return;};


bool Reload::isActionPossible(){
  return ((isInThePack(this->g))
	  && (isInThePack( this->ammu))
	  );
};
void Reload::doAction () {return;};



bool Attack::isActionPossible(){
  return ((isInThePack(this-> weap))
	  && ( (this->weap)->getRange() <= distance (this->vict) )
	  );
};
void Attack::doAction () {return;};


void newMovement (NewMov n){
  //TODO
  return;
};
