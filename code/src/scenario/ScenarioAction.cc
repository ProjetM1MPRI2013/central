#include "ScenarioAction.h"

ScenarioAction::ScenarioAction (std::string n, Simulation* s){
  simulation = s;
  name = n;
  date = 0; //TODO
}

ScenarioAction::ScenarioAction(const ScenarioAction& a){
  this->date = a.date;
  this->name = a.name;
  this->simulation = a.simulation;
}


void ScenarioAction::run(){
  return;
}

//AbstractMessage function implementations
std::string ScenarioAction::getMsgType(){
  std::string s ("H_SACTIO");
  return s;
}

std::string & ScenarioAction::toString(){
  std::string s ("TODO");
  return s;
}

AbstractMessage* ScenarioAction::fromString(std::string& msg){
  return ((AbstractMessage*)new ScenarioAction("TODO", NULL));
}

AbstractMessage* ScenarioAction::copy(){
  return ((AbstractMessage*)new ScenarioAction(*this));
}
