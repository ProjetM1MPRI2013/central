#include "ScenarioAction.h"

ScenarioAction::ScenarioAction (std::string n,int playerID, Simulation* s){
  simulation = s;
  name = n;
  date = 0;
  this->playerID =playerID;
}

ScenarioAction::ScenarioAction (std::string n, Simulation* s){
  simulation = s;
  name = n;
  date = 0;
  this->playerID =0; /*WILL BE USED FOR THE MAYOR*/
}
ScenarioAction::ScenarioAction(const ScenarioAction& a){
  this->date = a.date;
  this->name = a.name;
  this->simulation = a.simulation;
  this->playerID = a.playerID;
}


void ScenarioAction::run(){
  return;
}

//AbstractMessage function implementations
ScenarioAction::ScenarioAction() : date(0), name(){}

AbstractMessage* ScenarioAction::copy(){
  return ((AbstractMessage*)new ScenarioAction(*this));
}
