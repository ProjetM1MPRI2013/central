
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#include "PreScenarioActionList.h"
#ifndef SCENARIOACTIONLIST_H
#define SCENARIOACTIONLIST_H
class CoA_Pick: public ScenarioAction {
public:
CoA_Pick(int fake, std::pair<int,int> zone, int playerID,Simulation* s);
CoA_Pick(const CoA_Pick&);
public:
int fake; 
public:
std::pair<int,int> zone; 
public: 
 virtual void run (); 
  virtual AbstractMessage* copy();
protected :
//Serialization
CoA_Pick(){};
SIMPLE_MESSAGE(CoA_Pick, ScenarioAction, fake, zone);
};
class CoA_Kick: public ScenarioAction {
public:
CoA_Kick(int weapon, boost::uuids::uuid victim, int playerID,Simulation* s);
CoA_Kick(const CoA_Kick&);
public:
int weapon; 
public:
boost::uuids::uuid victim; 
public: 
 virtual void run (); 
  virtual AbstractMessage* copy();
protected :
//Serialization
CoA_Kick(){};
SIMPLE_MESSAGE(CoA_Kick, ScenarioAction, weapon, victim);
};
class CoA_Shoot: public ScenarioAction {
public:
CoA_Shoot(int gun, boost::uuids::uuid victim, int playerID,Simulation* s);
CoA_Shoot(const CoA_Shoot&);
public:
int gun; 
public:
boost::uuids::uuid victim; 
public: 
 virtual void run (); 
  virtual AbstractMessage* copy();
protected :
//Serialization
CoA_Shoot(){};
SIMPLE_MESSAGE(CoA_Shoot, ScenarioAction, gun, victim);
};
class CoA_Reload: public ScenarioAction {
public:
CoA_Reload(int gun, int ammunition, int playerID,Simulation* s);
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
CoA_Plant(int bomb, std::pair<int,int> zone, int playerID,Simulation* s);
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
CoA_Drop(int stuff, std::pair<int,int> zone, int playerID,Simulation* s);
CoA_Drop(const CoA_Drop&);
public:
int stuff; 
public:
std::pair<int,int> zone; 
public: 
 virtual void run (); 
  virtual AbstractMessage* copy();
protected :
//Serialization
CoA_Drop(){};
SIMPLE_MESSAGE(CoA_Drop, ScenarioAction, stuff, zone);
};
#endif