#include "ActionsTerro.h"

/*to ask to denys to implemente */
int distance(NPC* npc) {return 0;};
bool isPlantable (Tile* t) {return true;};

std::string stringOfActions (Actions a) {
	switch (a)
		{
			case DROP :
				return "Drop";
			break;
			case ATTACK :
				return "Attack";
			break;
			case RELOAD :
				return "Reload";
			break;
			case PLANT :
				return "Plant";
			break;
		};
};


bool isInThePack(Simulation* s, Stuff* stuff) {
  std::list<Stuff*> inventory = s->getPlayer()->getInventory();
  for (std::list<Stuff*>::iterator it = inventory.begin(); it != inventory.end(); ++it){
    if ((*it)->stuffID == stuff->stuffID){return true;};
  };
  return false;
};

Drop :: Drop (Stuff* s, Simulation* sim) : Action ("Drop",sim) {
  stu = s;
};

Attack :: Attack (Weapon* weapon,NPC* victim, Simulation* sim)  : Action ("Attack",sim) {
  vict = victim;
  weap = weapon;
};


Plant :: Plant (Bomb* bomb,Tile* zone, Simulation* sim)  : Action ("Plant",sim) {
  bo = bomb;
  z = zone;
};

Reload :: Reload (Gun* gun, Ammunition* ammunition, Simulation* sim) : Action ("Reload",sim) {
  g = gun;
  ammu = ammunition;
};

bool Drop::isActionPossible(){return isInThePack(this->simulation,this->stu);};
void Drop::doAction () {return;};


bool Plant::isActionPossible(){
  return (
	  (isInThePack(this->simulation,this->bo)) 
	  && (isPlantable (this->z))
	  );
};
void Plant::doAction () {return;};


bool Reload::isActionPossible(){
  return ((isInThePack(this->simulation,this->g))
	  && (isInThePack(this->simulation,this->ammu))
	  );
};
void Reload::doAction () {return;};



bool Attack::isActionPossible(){
  return ((isInThePack(this->simulation,this-> weap))
	  && ( (this->weap)->getRange() <= distance (this->vict) )
	  );
};
void Attack::doAction () {return;};


void newMovement (NewMov n){
  //TODO
  return;
};
