
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#include "PreActionTerro.h"
#include "simulation/npc.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>
#include "Action.h"
#include "StuffList.h"
#include "simulation/npc.h"
#include "generation/tile.h"
#include "Actions.h"
#include "ScenarioActionList.h"
#include "NewMov.h"
#include "tile.h"
#include "position.h"
#include "npc.h"
#include "localState.h"
#include "globalState.h"
#ifndef ACTIONTERRO_H
#define ACTIONTERRO_H

/*********************************************************
** Attack**
*********************************************************/
class A_Attack: public Action {
public:
A_Attack  (int weapon, int victim, LocalState* s);
A_Attack(const A_Attack&);
public:
int weapon; 
public:
int victim; 
public: 
 bool isActionPossible (); 
  void doAction (); 
  void addPendingActions(GlobalState* gs); 
  virtual AbstractMessage* copy();
protected :
//Serialization
A_Attack(){};
SIMPLE_MESSAGE(A_Attack, Action, weapon, victim);
};
/*********************************************************
** Reload**
*********************************************************/
class A_Reload: public Action {
public:
A_Reload  (int gun, int ammunition, LocalState* s);
A_Reload(const A_Reload&);
public:
int gun; 
public:
int ammunition; 
public: 
 bool isActionPossible (); 
  void doAction (); 
  void addPendingActions(GlobalState* gs); 
  virtual AbstractMessage* copy();
protected :
//Serialization
A_Reload(){};
SIMPLE_MESSAGE(A_Reload, Action, gun, ammunition);
};
/*********************************************************
** Plant**
*********************************************************/
class A_Plant: public Action {
public:
A_Plant  (int bomb, std::pair<int,int> zone, LocalState* s);
A_Plant(const A_Plant&);
public:
int bomb; 
public:
std::pair<int,int> zone; 
public: 
 bool isActionPossible (); 
  void doAction (); 
  void addPendingActions(GlobalState* gs); 
  virtual AbstractMessage* copy();
protected :
//Serialization
A_Plant(){};
SIMPLE_MESSAGE(A_Plant, Action, bomb, zone);
};
/*********************************************************
** Drop**
*********************************************************/
class A_Drop: public Action {
public:
A_Drop  (int stuff, LocalState* s);
A_Drop(const A_Drop&);
public:
int stuff; 
public:
int getplayerID ();
public:
void setplayerID (int);
protected:
int playerID; 
public: 
 bool isActionPossible (); 
  void doAction (); 
  void addPendingActions(GlobalState* gs); 
  virtual AbstractMessage* copy();
protected :
//Serialization
A_Drop(){};
SIMPLE_MESSAGE(A_Drop, Action, stuff, playerID);
};
#endif