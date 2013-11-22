#include "HScenario.h"

HScenario::HScenario (Simulation* s) {
  simulation = s;
  ScenarioAction::setSimulation(s);
};

void HScenario::run(){
  return;
};

void HScenario::eventTriggered (EventType e, EventTarget& t){
  return;
};
