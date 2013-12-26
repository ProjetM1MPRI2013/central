#include "HScenario.h"
#include "simulation.h"

#define DEBUG true

HScenario::HScenario (Simulation& s) : simulation(s) {
  subscribe("NPC::created", simulation, &HScenario::createdNPC);
};

void HScenario::run(){
  
  return;
};

void HScenario::eventTriggered (EventName e, EventTarget& t){
  return;
};

void HScenario::createdNPC(Simulation& s, NPC& npc) {
  if (DEBUG) { std::cout << "NPC was created" << std::endl; }
  //std::function<void(EventName, NPC&)> fn = [this](EventName e, NPC& npc) { this->arrivedNPC(npc); } ;
  subscribe("NPC::arrived", npc, &HScenario::arrivedNPC);
}

void HScenario::arrivedNPC(NPC& npc) {
  if (DEBUG) { std::cout << "NPC has arrived" << std::endl; }
}
