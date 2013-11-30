#include "HScenario.h"

HScenario::HScenario (Simulation* s) {
  simulation = s;
  ScenarioAction::setSimulation(s);
};

void HScenario::run(){
  return;
};

void HScenario::eventTriggered (EventName e, EventTarget& t){
  return;
};
