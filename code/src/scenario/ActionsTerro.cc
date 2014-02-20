
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#include "ActionsTerro.h"

/*********************************************************
** Shoot**
*********************************************************/

A_Shoot::A_Shoot (int gun, boost::uuids::uuid victim, LocalState* sim) : Action ( "ToA_Shoot", sim) {
this->gun = (int)gun;
this->victim = (boost::uuids::uuid)victim;
};

A_Shoot::A_Shoot(const A_Shoot& a) : Action(" ToA_Shoot", a.simulation){
this->gun= a.gun;
this->victim= a.victim;
};

void A_Shoot::doAction() {
this->simulation->getClient()->sendMessage<Action>(*this,true);
};

bool A_Shoot::isActionPossible() {
return true;
//return (isInThePack (this->simulation,this->gun))&&(((((C_Gun*)(&((Simulation*)this->simulation)->getItemByID<C_Gun>(this->gun)))))->getrange()<=distance (this->simulation,(this->simulation->getNPCByID(this->victim))));
};

void A_Shoot::addPendingActions(GlobalState* gs){
gs->addAction(new CoA_Shoot (this->gun, this->victim, ((Action*)this)->playerID,(Simulation*) gs));
gs->deleteAction(this);
};

AbstractMessage* A_Shoot::copy() {
return (AbstractMessage*) new A_Shoot(*this);
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
this->simulation->getClient()->sendMessage<Action>(*this,true);
};

bool A_Reload::isActionPossible() {
return true;
//return (isInThePack (this->simulation,this->gun))&&(isInThePack (this->simulation,this->ammunition));
};

void A_Reload::addPendingActions(GlobalState* gs){
gs->addAction(new CoA_Reload (this->gun, this->ammunition, ((Action*)this)->playerID,(Simulation*) gs));
gs->deleteAction(this);
};

AbstractMessage* A_Reload::copy() {
return (AbstractMessage*) new A_Reload(*this);
};

/*********************************************************
** Plant**
*********************************************************/

A_Plant::A_Plant (int bomb, std::pair<int,int> zone, LocalState* sim) : Action ( "ToA_Plant", sim) {
this->bomb = (int)bomb;
this->zone = (std::pair<int,int>)zone;
};

A_Plant::A_Plant(const A_Plant& a) : Action(" ToA_Plant", a.simulation){
this->bomb= a.bomb;
this->zone= a.zone;
};

void A_Plant::doAction() {
this->simulation->getClient()->sendMessage<Action>(*this,true);
};

bool A_Plant::isActionPossible() {
return true;
//return (isInThePack (this->simulation,this->bomb))&&(isPlantable((Tile*) ((Simulation*)this->simulation)->getMap()->getTile(this->zone)));
};

void A_Plant::addPendingActions(GlobalState* gs){
gs->addAction(new CoA_Plant (this->bomb, this->zone, ((Action*)this)->playerID,(Simulation*) gs));
gs->deleteAction(this);
};

AbstractMessage* A_Plant::copy() {
return (AbstractMessage*) new A_Plant(*this);
};

/*********************************************************
** Drop**
*********************************************************/

A_Drop::A_Drop (int stuff, std::pair<int,int> zone, LocalState* sim) : Action ( "ToA_Drop", sim) {
this->stuff = (int)stuff;
this->zone = (std::pair<int,int>)zone;
};

A_Drop::A_Drop(const A_Drop& a) : Action(" ToA_Drop", a.simulation){
this->stuff= a.stuff;
this->zone= a.zone;
};

void A_Drop::doAction() {
this->simulation->getClient()->sendMessage<Action>(*this,true);
};

bool A_Drop::isActionPossible() {
return true;
//return (isInThePack(this->simulation,this->stuff));
};

void A_Drop::addPendingActions(GlobalState* gs){
gs->addAction(new CoA_Drop (this->stuff, this->zone, ((Action*)this)->playerID,(Simulation*) gs));
gs->deleteAction(this);
};

AbstractMessage* A_Drop::copy() {
return (AbstractMessage*) new A_Drop(*this);
};
