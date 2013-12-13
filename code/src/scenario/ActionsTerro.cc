#include "ActionsTerro.h"
#include <iostream>
#include <list>
#include "network/client.h"

/*to ask to denys to implemente */
bool isPlantable (Tile* t) {
switch(t->getType())
// todo choisir les quelles sont plantables
	{case(ROADH) : return true;
	case(ROADV) : return true;
	case(INTER) : return true;
	case(BANK) : return false;
	case(HOUSE): return false;
	case(BLANK): return false;
	default: return false;
	};
 return false;
};

float distance(Simulation* s, NPC* npc) {
	return s->getPlayer()->getPosition()->distance(npc->getPosition());
};



bool isInThePack(Simulation* s, Stuff* stuff) {
  std::list<Stuff*> inventory = s->getPlayer()->getInventory();
  for (std::list<Stuff*>::iterator it = inventory.begin(); it != inventory.end(); ++it){
    if ((*it)->stuffID == stuff->stuffID){return true;};
  };
  return false;
};


void SoNOfActions(Actions a,std::list<SoN> l) {
  switch (a)
    {
    case DROP : break;
    case ATTACK :
      l.push_front(SON_NPC);
    break;
    case RELOAD :
      l.push_front(SON_STUFF);
    break;
    case PLANT :
    break;
    default:
      std::cerr << "Stack.cc : error in SoNOfActions \n";
      break;
    };
};


Drop :: Drop (Stuff* s, Simulation* sim) : Action ("Drop",sim) {
  stu = s;
  this->playerID = this->simulation->getPlayer()->getID();
};

Drop::Drop(const Drop& d) : Action ("Drop",d.simulation){
  this->stu = d.stu;
  this->playerID = d.playerID;
}

Attack :: Attack (Weapon* weapon,NPC* victim, Simulation* sim)  : Action ("Attack",sim) {
  vict = victim;
  weap = weapon;
};

Attack::Attack(const Attack& a) : Action("Attack", a.simulation){
  this->weap = a.weap;
  this->vict = a.vict;
}


Plant :: Plant (Bomb* bomb,Tile* zone, Simulation* sim)  : Action ("Plant",sim) {
  bo = bomb;
  z = zone;
};

Plant::Plant (const Plant& p) : Action ("Plant", p.simulation){
  this->bo = p.bo;
  this->z = p.z;
}


Reload :: Reload (Gun* gun, Ammunition* ammunition, Simulation* sim) : Action ("Reload",sim) {
  g = gun;
  ammu = ammunition;
};

Reload::Reload(const Reload& r) : Action("Reload", r.simulation){
  this->g = r.g;
  this->ammu = r.ammu;
};


bool Drop::isActionPossible(){return isInThePack(this->simulation,this->stu);};
void Drop::doAction () {this->simulation->getClient()->sendMessage(*this,true);};

void Drop::addPendingActions(HostSimulation* hs){
  hs->addAction(new DropItem(this->stu,this->playerID, (Simulation*) hs));
  hs->deleteAction(this);
}


bool Plant::isActionPossible(){
  return (
	  (isInThePack(this->simulation,this->bo)) 
	  && (isPlantable (this->z))
	  );
};
void Plant::doAction () {this->simulation->getClient()->sendMessage(*this,true);};

void Plant::addPendingActions(HostSimulation* hs){
  //Pour l'instant on fait exploser la bombe directement. Et on ne la supprime pas de l'inventaire.
  hs->addAction(new Explosion(this->z,this->bo->getPower(),(Simulation*)hs));
  hs->deleteAction(this);
}


bool Reload::isActionPossible(){
  return ((isInThePack(this->simulation,this->g))
	  && (isInThePack(this->simulation,this->ammu))
	  );
};
void Reload::doAction () {this->simulation->getClient()->sendMessage(*this,true);};

void Reload::addPendingActions(HostSimulation* hs){
  //TODO
  hs->deleteAction(this);
}



bool Attack::isActionPossible(){
  return ((isInThePack(this->simulation,this-> weap))
	  && ( (this->weap)->getRange() <= distance (this->simulation,this->vict) )
	  );
};
void Attack::doAction () {this->simulation->getClient()->sendMessage(*this,true);};

void Attack::addPendingActions(HostSimulation* hs){
  hs->addAction(new KillNPC(this->vict, (Simulation*)hs));
  hs->deleteAction(this);
}


void newMovement (NewMov n, Simulation* s){
  NewMovNetwork newMov(n,s->getPlayer()->getID());
  std::cout << "Client : New Movement from player : " << s->getPlayer()->getID() << " ";
  printNewMov(n);
  std::cout << std::endl;
  s->getClient()->sendMessage(newMov,true);

  s->addAction((ScenarioAction *) new ChangeDirection( s->getPlayer()->getID(),n,s));

  return;
};


/***********************************
 * AbstractMessage implementations *
 **********************************/

AbstractMessage* Drop::copy(){
    return (AbstractMessage*) new Drop(*this);
}

AbstractMessage* Attack::copy(){
  return (AbstractMessage*) new Attack(*this);
}

AbstractMessage* Plant::copy(){
  return (AbstractMessage*) new Plant(*this);
}

AbstractMessage* Reload::copy(){
  return (AbstractMessage*) new Reload(*this);
}
