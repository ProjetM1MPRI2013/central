#include "HScenario.h"
#include "simulation.h"

#define DEBUG false

HScenario::HScenario (Simulation& s) : simulation(s) {
};

void HScenario::run(){
  
  return;
};

void HScenario::eventTriggered (EventName e, EventTarget& t){
  return;
};

void HScenario::createdNPC(NPC& npc) {
  std::function<void(EventName, NPC&)> fn = [this](EventName e, NPC& npc) { this->arrivedNPC(npc); } ;
  subscribe("NPC::arrived", npc, fn);
}

void HScenario::arrivedNPC(NPC& npc) {
  if (DEBUG) { std::cout << "NPC has arrived" << std::endl; }
}
