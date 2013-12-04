#include "ScenarioAction.h"

Simulation* ScenarioAction::simulation = 0;

ScenarioAction::ScenarioAction (std::string n){
  name = n;
  date = 0; //TODO
};


void ScenarioAction::run(){
  return;
};
