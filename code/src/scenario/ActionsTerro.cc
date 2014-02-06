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


void newMovement (NewMov n, Simulation* s){
	NewMovNetwork newMovNet(n,s->getPlayer()->getID());
	std::cout << "Client : New Movement from player : " << s->getPlayer()->getID() << " ";
	printNewMov(n);
	std::cout << std::endl;
	s->getClient()->sendMessage(newMovNet,true);
};


/*********************************************************
** Generated code**
*********************************************************/

/*********************************************************
** Attack**
*********************************************************/

A_Attack::A_Attack (int weapon, int victim, LocalState* sim) : Action ( "ToA_Attack", sim) {
this->weapon = (int)weapon;
this->victim = (int)victim;
};

A_Attack::A_Attack(const A_Attack& a) : Action(" ToA_Attack", a.simulation){
this->weapon= a.weapon;
this->victim= a.victim;
};

void A_Attack::doAction() {
this->simulation->getClient()->sendMessage(*this,true);
};

bool A_Attack::isActionPossible() {
return true;
//return (isInThePack (this->simulation,this->weapon))&&((this->weapon)->getRange()<=distance (this->simulation,this->victim));
};

void A_Attack::addPendingActions(GlobalState* gs){
//gs->addAction(new CoA_Attack (this->weapon, this->victim, (Simulation*) gs));
gs->deleteAction(this);
};

AbstractMessage* A_Attack::copy() {
return (AbstractMessage*) new A_Attack(*this);
};

/*********************************************************
** Reload**
*********************************************************/

A_Reload::A_Reload (int gun, int ammunition, LocalState* sim) : Action ( "ToA_Reload", sim) {
this->gun = (int)gun;
this->ammunition = (int)ammunition;
};

A_Reload::A_Reload(const A_Reload& a) : Action(" ToA_Reload", a.simulation){
this->gun= a.gun;
this->ammunition= a.ammunition;
};

void A_Reload::doAction() {
this->simulation->getClient()->sendMessage(*this,true);
};

bool A_Reload::isActionPossible() {
return true;
//return (isInThePack (this->simulation,this->gun))&&(isInThePack (this->simulation,this->ammunition));
};

void A_Reload::addPendingActions(GlobalState* gs){
//gs->addAction(new CoA_Reload (this->gun, this->ammunition, (Simulation*) gs));
gs->deleteAction(this);
};

AbstractMessage* A_Reload::copy() {
return (AbstractMessage*) new A_Reload(*this);
};

/*********************************************************
** Plant**
*********************************************************/

A_Plant::A_Plant (int bomb, int zone, LocalState* sim) : Action ( "ToA_Plant", sim) {
this->bomb = (int)bomb;
this->zone = (int)zone;
};

A_Plant::A_Plant(const A_Plant& a) : Action(" ToA_Plant", a.simulation){
this->bomb= a.bomb;
this->zone= a.zone;
};

void A_Plant::doAction() {
this->simulation->getClient()->sendMessage(*this,true);
};

bool A_Plant::isActionPossible() {
return true;
//return (isInThePack (this->simulation,this->bomb))&&(isPlantable(this->zone));
};

void A_Plant::addPendingActions(GlobalState* gs){
//gs->addAction(new CoA_Plant (this->bomb, this->zone, (Simulation*) gs));
gs->deleteAction(this);
};

AbstractMessage* A_Plant::copy() {
return (AbstractMessage*) new A_Plant(*this);
};

/*********************************************************
** Drop**
*********************************************************/

A_Drop::A_Drop (int stuff, LocalState* sim) : Action ( "ToA_Drop", sim) {
this->stuff = (int)stuff;
this->playerID = (int)(this->simulation->getPlayer()->getID());
};

A_Drop::A_Drop(const A_Drop& a) : Action(" ToA_Drop", a.simulation){
this->stuff= a.stuff;
this->playerID= a.playerID;
};

void A_Drop::doAction() {
this->simulation->getClient()->sendMessage(*this,true);
};

bool A_Drop::isActionPossible() {
return true;
//return ((isInThePack(this->simulation,this->g)) && (isInThePack(this->simulation,this->ammu));
};

void A_Drop::addPendingActions(GlobalState* gs){
//gs->addAction(new CoA_Drop (this->stuff, this->playerID, (Simulation*) gs));
gs->deleteAction(this);
};

AbstractMessage* A_Drop::copy() {
return (AbstractMessage*) new A_Drop(*this);
};
