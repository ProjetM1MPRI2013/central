#include"ActionsTerro.h"



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

void newMovement (NewMov n, LocalState* s){
	std::cout << "Client : New Movement begin\n";
	NewMovNetwork newMovNet(n,s->getOwner().getID(),s);
	std::cout << "Client : New Movement from player : " << s->getOwner().getID() << " ";
	printNewMov(n);
	std::cout << std::endl;
	s->getOwner().setDirection(newMovNet.newDirection);
	s->getClient()->sendMessage(newMovNet,true);
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
	this->simulation->getClient()->sendMessage<Action>(*this,true);
};

bool A_Drop::isActionPossible() {
	//return true;
	return (
			(isInThePack(this->simulation,this->stuff))
			);
};

void A_Drop::addPendingActions(GlobalState* gs){
	//gs->addAction(new CoA_Drop (this->stuff, this->playerID, (Simulation*) gs));
	gs->deleteAction(this);
};

AbstractMessage* A_Drop::copy() {
	return (AbstractMessage*) new A_Drop(*this);
};
