#ifndef MAIN
#define MAIN
#include "simulation/simulation.h"
#include "graphism/graphic_context_iso.h"
#include <random>
namespace dummy {
  void createNPCs(int number, Simulation& simu, Geography& geo, std::default_random_engine npcGen);
}
#endif
