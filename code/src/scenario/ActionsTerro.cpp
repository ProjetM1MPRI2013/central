#include "ActionsTerro.h"

/*to ask to denys to implemente */
bool isInThePack(Stuff stuff) { return true ;};
int distance(NPC npc) {return 0;};
bool isPlantable (Tile t) {return true;};

Drop :: Drop (Stuff* s) : Action ("Drop") {
  stu = s;
};

Attack :: Attack (Weapon* weapon,NPC* victim)  : Action ("Attack") {
  vict = victim;
  weap = weapon;
};


Plant :: Plant (Bomb* bomb,Tile zone )  : Action ("Plant") {
  bo = bomb;
  z = zone;
};

Reload :: Reload (Gun gun,Ammunition ammunition) : Action ("Reload") {
  g = gun;
  ammu = ammunition;
};

bool Drop::isActionPossible(){return isInThePack(this->stu);};

bool Plant::isActionPossible(){
  return (
	  (isInThePack(this->bo)) 
	  && (isPlantable (this->z))
	  );
};

bool Reload::isActionPossible(){
  return ((isInThePack(this->g))
	  && (isInThePack( this->ammu))
	  );
};


bool Attack::isActionPossible(){
  return ((isInThePack(this-> weap))
	  && ( (this->weap).range <= distance (this->vict) )
	  );
};
