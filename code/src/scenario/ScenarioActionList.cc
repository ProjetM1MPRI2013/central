
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#include "ScenarioActionList.h"

/*********************************************************
** Consequences of Shoot**
*********************************************************/
CoA_Shoot::CoA_Shoot(int gun, boost::uuids::uuid victim, int playerID,Simulation* sim)
: ScenarioAction("Shoot",playerID,sim){ 
this->gun = (int)gun;
this->victim = (boost::uuids::uuid)victim;
};

CoA_Shoot::CoA_Shoot(const CoA_Shoot& a) : ScenarioAction("Shoot",a.playerID, a.simulation){
this->gun= a.gun;
this->victim= a.victim;
};

AbstractMessage* CoA_Shoot::copy() {
return (AbstractMessage*) new CoA_Shoot(*this);
};

void CoA_Shoot::run () {
KillNPC(victim,simulation);
;};


/*********************************************************
** Consequences of Reload**
*********************************************************/
CoA_Reload::CoA_Reload(int gun, int ammunition, int playerID,Simulation* sim)
: ScenarioAction("Reload",playerID,sim){ 
this->gun = (int)gun;
this->ammunition = (int)ammunition;
};

CoA_Reload::CoA_Reload(const CoA_Reload& a) : ScenarioAction("Reload",a.playerID, a.simulation){
this->gun= a.gun;
this->ammunition= a.ammunition;
};

AbstractMessage* CoA_Reload::copy() {
return (AbstractMessage*) new CoA_Reload(*this);
};

void CoA_Reload::run () {
;};


/*********************************************************
** Consequences of Plant**
*********************************************************/
CoA_Plant::CoA_Plant(int bomb, std::pair<int,int> zone, int playerID,Simulation* sim)
: ScenarioAction("Plant",playerID,sim){ 
this->bomb = (int)bomb;
this->zone = (std::pair<int,int>)zone;
};

CoA_Plant::CoA_Plant(const CoA_Plant& a) : ScenarioAction("Plant",a.playerID, a.simulation){
this->bomb= a.bomb;
this->zone= a.zone;
};

AbstractMessage* CoA_Plant::copy() {
return (AbstractMessage*) new CoA_Plant(*this);
};

void CoA_Plant::run () {
	C_Bomb* b =(C_Bomb*) (&this->simulation->getItemByID<C_Bomb>(this->bomb));
	Explosion(b->getpower(),this->zone,this->simulation);
	DropItem(this->bomb,this->playerID,this->simulation);
;};


/*********************************************************
** Consequences of Drop**
*********************************************************/
CoA_Drop::CoA_Drop(int stuff, std::pair<int,int> zone, int playerID,Simulation* sim)
: ScenarioAction("Drop",playerID,sim){ 
this->stuff = (int)stuff;
this->zone = (std::pair<int,int>)zone;
};

CoA_Drop::CoA_Drop(const CoA_Drop& a) : ScenarioAction("Drop",a.playerID, a.simulation){
this->stuff= a.stuff;
this->zone= a.zone;
};

AbstractMessage* CoA_Drop::copy() {
return (AbstractMessage*) new CoA_Drop(*this);
};

void CoA_Drop::run () {
	simulation->getMap()->getTile(this->zone)->addStuff((Clickable*)(&this->simulation->getItemByID<C_Stuff>(this->stuff)));
	DropItem(this->stuff,this->playerID,this->simulation);
};

