#include "HScenario.h"
#include "simulation.h"

#define DEBUG false

HScenario::HScenario (Simulation& s) : simulation(s) {
  subscribe("NPC::created",simulation, this, &HScenario::createdNPC);
};

void HScenario::run(){
  
  return;
};

void HScenario::eventTriggered (EventName e, EventTarget& t){
  return;
};

void HScenario::createdNPC(EventName e, Simulation& s, NPC& npc) {
  if (DEBUG) { std::cout << "NPC was created" << std::endl; }
  //std::function<void(EventName, NPC&)> fn = [this](EventName e, NPC& npc) { this->arrivedNPC(npc); } ;
  subscribe("NPC::arrived", npc, this, &HScenario::arrivedNPC);
}

void HScenario::arrivedNPC(EventName e, NPC& npc) {
  if (DEBUG) { std::cout << "NPC has arrived" << std::endl; }
}
