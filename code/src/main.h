#ifndef MAIN
#define MAIN
#include "simulation/simulation.h"
#include "graphism/graphic_context_iso.h"
namespace dummy {
  void createNPCs(int number, Simulation& simu, GraphicContextIso& graContIso, Geography& geo, std::default_random_engine npcGen);
}
#endif
