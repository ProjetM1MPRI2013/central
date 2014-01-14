#include "HScenario.h"
#include "simulation.h"

#define DEBUG false
#include "debug.h"

HScenario::HScenario (Simulation& s) : simulation(s) {
  listen("NPC::created", simulation, &HScenario::createdNPC);
};

void HScenario::run(){
  return;
};

void HScenario::createdNPC(Simulation& s, NPC& npc) {
  DBG << "NPC was created";
  //std::function<void(EventName, NPC&)> fn = [this](EventName e, NPC& npc) { this->arrivedNPC(npc); } ;
  listen("NPC::arrived", npc, &HScenario::arrivedNPC);
}

void HScenario::arrivedNPC(NPC& npc) {
  DBG << "NPC has arrived";
}
