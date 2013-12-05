#include "HScenario.h"
#include "simulation.h"

HScenario::HScenario (Simulation* s) {
  simulation = s;
  ScenarioAction::simulation = s;
};

void HScenario::run(){
  
  return;
};

void HScenario::eventTriggered (EventName e, EventTarget& t){
  return;
};
