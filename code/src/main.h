#ifndef MAIN
#define MAIN
#include "simulation/simulation.h"
#include "graphism/graphic_context_iso.h"
#include <random>
namespace dummy {
  void createNPCs(int number, LocalState& simu, GraphicContextIso& graContIso, Geography& geo, std::default_random_engine npcGen);
}
#endif
