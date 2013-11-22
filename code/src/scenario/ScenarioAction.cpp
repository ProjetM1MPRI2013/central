#include "ScenarioAction.h"

ScenarioAction::ScenarioAction (std::string n){
  name = n;
  date = 0; //TODO
};

void ScenarioAction::setSimulation (Simulation* s){
  this.simulation = s;
  return;
};

void ScenarioAction::run(){
  return;
};
