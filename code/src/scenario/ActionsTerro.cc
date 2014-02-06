#include "ActionsTerro.h"
#include <iostream>
#include <list>

#include "localState.h"
#include "globalState.h"

#include "network/client.h"
#define DEBUG false
#include "debug.h"

bool isPlantable (Tile* t) {
	if (DEBUG) {std::cout << "nobody isPLANTABLE" << std::endl ;};
switch(t->getType())
// todo choisir les quelles sont plantables
	{case(ROADH) : return true;
	case(ROADV) : return true;
	case(INTER) : return true;
	case(BANK) : return true;
	case(HOUSE): return true;
	case(BLANK): return true;
	default: return true;
	};
 return false;
};

float distance(LocalState* s, NPC* npc) {
  return s->getOwner().getPosition().distance(npc->getPosition());
};



bool isInThePack(LocalState* s, int stuffID) {
  return s->getOwner().hasItemByID(stuffID);
};



Drop :: Drop (int stuffID, LocalState* sim) : Action ("Drop",sim) {
  this->stuffID = stuffID;
  this->playerID = this->simulation->getOwner().getID();
};

Drop::Drop(const Drop& d) : Action ("Drop",d.simulation){
  this->stuffID = d.stuffID;
  this->playerID = d.playerID;
}

Attack :: Attack (int weaponID, NPC* victim, LocalState* sim)  : Action ("Attack",sim) {
  vict = victim;
  this->weaponID = weaponID;
};

Attack::Attack(const Attack& a) : Action("Attack", a.simulation){
  this->weaponID = a.weaponID;
  this->vict = a.vict;
}


Plant :: Plant (int bombID, Tile* zone, LocalState* sim)  : Action ("Plant",sim) {
  this->bombID = bombID;
  z = zone;
};

Plant::Plant (const Plant& p) : Action ("Plant", p.simulation){
  this->bombID = p.bombID;
  this->z = p.z;
}


Reload :: Reload (int gunID, int ammunitionID, LocalState* sim) : Action ("Reload",sim) {
  this->gunID = gunID;
  this->ammunitionID = ammunitionID;
};

Reload::Reload(const Reload& r) : Action("Reload", r.simulation){
  this->gunID = r.gunID;
  this->ammunitionID = r.ammunitionID;
};


bool Drop::isActionPossible(){return isInThePack(this->simulation,this->stuffID);};
void Drop::doAction () {
    this->simulation->getClient()->sendMessage(*this,true);
};

void Drop::addPendingActions(GlobalState* hs){
  hs->addAction(new DropItem(this->stuffID,this->playerID, (Simulation*) hs));
  hs->deleteAction(this);
}


bool Plant::isActionPossible(){
  return (
	  (isInThePack(this->simulation,this->bombID)) 
	  && (isPlantable (this->z))
	  );
};
void Plant::doAction () {
    this->simulation->getClient()->sendMessage(*this,true);
};

void Plant::addPendingActions(GlobalState* hs){
  //Pour l'instant on fait exploser la bombe directement. Et on ne la supprime pas de l'inventaire.

    Bomb bomb = hs->getItemByID<Bomb>(bombID);
    hs->addAction(new Explosion(this->z,bomb.getPower(),(Simulation*)hs));
    hs->deleteAction(this);
}


bool Reload::isActionPossible(){
  return ((isInThePack(this->simulation,this->gunID))
	  && (isInThePack(this->simulation,this->ammunitionID))
	  );
};
void Reload::doAction () {this->simulation->getClient()->sendMessage(*this,true);};

void Reload::addPendingActions(GlobalState* hs){
  //TODO
  hs->deleteAction(this);
}



bool Attack::isActionPossible(){

  return ((isInThePack(this->simulation,this->weaponID))
	  && ( this->simulation->getItemByID<Weapon>(weaponID)).getRange() <= distance (this->simulation,this->vict) ) ;
};
void Attack::doAction () {this->simulation->getClient()->sendMessage(*this,true);};

void Attack::addPendingActions(GlobalState* hs){
  hs->addAction(new KillNPC(this->vict, (Simulation*)hs));
  hs->deleteAction(this);
}


void newMovement (NewMov n, Simulation* s){
  NewMovNetwork newMovNet(n,s->getPlayer()->getID());
  std::cout << "Client : New Movement from player : " << s->getPlayer()->getID() << " ";
  printNewMov(n);
  std::cout << std::endl;
  s->getClient()->sendMessage(newMovNet,true);

  //s->addAction((ScenarioAction *) new ChangeDirection( s->getPlayer()->getID(),n,s));

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
