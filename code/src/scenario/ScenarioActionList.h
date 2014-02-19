
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#include "PreScenarioActionList.h"
#ifndef SCENARIOACTIONLIST_H
#define SCENARIOACTIONLIST_H
class CoA_Attack: public ScenarioAction {
public:
CoA_Attack(int weapon, boost::uuids::uuid victim, Simulation* s);
CoA_Attack(const CoA_Attack&);
public:
int weapon; 
public:
boost::uuids::uuid victim; 
public: 
 virtual void run (); 
  virtual AbstractMessage* copy();
protected :
//Serialization
CoA_Attack(){};
SIMPLE_MESSAGE(CoA_Attack, ScenarioAction, weapon, victim);
};
class CoA_Reload: public ScenarioAction {
public:
CoA_Reload(int gun, int ammunition, Simulation* s);
CoA_Reload(const CoA_Reload&);
public:
int gun; 
public:
int ammunition; 
public: 
 virtual void run (); 
  virtual AbstractMessage* copy();
protected :
//Serialization
CoA_Reload(){};
SIMPLE_MESSAGE(CoA_Reload, ScenarioAction, gun, ammunition);
};
class CoA_Plant: public ScenarioAction {
public:
CoA_Plant(int bomb, std::pair<int,int> zone, Simulation* s);
CoA_Plant(const CoA_Plant&);
public:
int bomb; 
public:
std::pair<int,int> zone; 
public: 
 virtual void run (); 
  virtual AbstractMessage* copy();
protected :
//Serialization
CoA_Plant(){};
SIMPLE_MESSAGE(CoA_Plant, ScenarioAction, bomb, zone);
};
class CoA_Drop: public ScenarioAction {
public:
CoA_Drop(int stuff, int playerID, Simulation* s);
CoA_Drop(const CoA_Drop&);
public:
int stuff; 
public:
int playerID; 
public: 
 virtual void run (); 
  virtual AbstractMessage* copy();
protected :
//Serialization
CoA_Drop(){};
SIMPLE_MESSAGE(CoA_Drop, ScenarioAction, stuff, playerID);
};
#endif