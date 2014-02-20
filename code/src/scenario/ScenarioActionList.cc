
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#include "ScenarioActionList.h"

/*********************************************************
** Consequences of Attack**
*********************************************************/
CoA_Attack::CoA_Attack(int weapon, boost::uuids::uuid victim, int playerID,Simulation* sim)
: ScenarioAction("Attack",playerID,sim){ 
this->weapon = (int)weapon;
this->victim = (boost::uuids::uuid)victim;
};

CoA_Attack::CoA_Attack(const CoA_Attack& a) : ScenarioAction("Attack",a.playerID, a.simulation){
this->weapon= a.weapon;
this->victim= a.victim;
};

AbstractMessage* CoA_Attack::copy() {
return (AbstractMessage*) new CoA_Attack(*this);
};

void CoA_Attack::run () {
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
Explosion(3,this->zone,this->simulation);
DropItem(this->bomb,this->playerID,this->simulation);
;};


/*********************************************************
** Consequences of Drop**
*********************************************************/
CoA_Drop::CoA_Drop(int stuff, int playerID,Simulation* sim)
: ScenarioAction("Drop",playerID,sim){ 
this->stuff = (int)stuff;
};

CoA_Drop::CoA_Drop(const CoA_Drop& a) : ScenarioAction("Drop",a.playerID, a.simulation){
this->stuff= a.stuff;
};

AbstractMessage* CoA_Drop::copy() {
return (AbstractMessage*) new CoA_Drop(*this);
};

void CoA_Drop::run () {
DropItem(this->stuff,this->playerID,this->simulation);
;};

