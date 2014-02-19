
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#include "ScenarioActionList.h"

/*********************************************************
** Consequences of Attack**
*********************************************************/
CoA_Attack::CoA_Attack(int weapon, boost::uuids::uuid victim, Simulation* sim)
: ScenarioAction("Attack",sim){ 
this->weapon = (int)weapon;
this->victim = (boost::uuids::uuid)victim;
};

CoA_Attack::CoA_Attack(const CoA_Attack& a) : ScenarioAction("Attack", a.simulation){
this->weapon= a.weapon;
this->victim= a.victim;
};

AbstractMessage* CoA_Attack::copy() {
return (AbstractMessage*) new CoA_Attack(*this);
};

void CoA_Attack::run () {
;};


/*********************************************************
** Consequences of Reload**
*********************************************************/
CoA_Reload::CoA_Reload(int gun, int ammunition, Simulation* sim)
: ScenarioAction("Reload",sim){ 
this->gun = (int)gun;
this->ammunition = (int)ammunition;
};

CoA_Reload::CoA_Reload(const CoA_Reload& a) : ScenarioAction("Reload", a.simulation){
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
CoA_Plant::CoA_Plant(int bomb, std::pair<int,int> zone, Simulation* sim)
: ScenarioAction("Plant",sim){ 
this->bomb = (int)bomb;
this->zone = (std::pair<int,int>)zone;
};

CoA_Plant::CoA_Plant(const CoA_Plant& a) : ScenarioAction("Plant", a.simulation){
this->bomb= a.bomb;
this->zone= a.zone;
};

AbstractMessage* CoA_Plant::copy() {
return (AbstractMessage*) new CoA_Plant(*this);
};

void CoA_Plant::run () {
Explosion(3,this->zone,this->simulation);
;};


/*********************************************************
** Consequences of Drop**
*********************************************************/
CoA_Drop::CoA_Drop(int stuff, int playerID, Simulation* sim)
: ScenarioAction("Drop",sim){ 
this->stuff = (int)stuff;
this->playerID = (int)(this->simulation->getPlayer()->getID());
};

CoA_Drop::CoA_Drop(const CoA_Drop& a) : ScenarioAction("Drop", a.simulation){
this->stuff= a.stuff;
this->playerID= a.playerID;
};

AbstractMessage* CoA_Drop::copy() {
return (AbstractMessage*) new CoA_Drop(*this);
};

void CoA_Drop::run () {
DropItem
;};

