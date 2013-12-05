#include "ScenarioAction.h"

ScenarioAction::ScenarioAction (std::string n,Simulation* s){
	simulation = s;
  name = n;
  date = 0; //TODO
};


void ScenarioAction::run(){
  return;
};
