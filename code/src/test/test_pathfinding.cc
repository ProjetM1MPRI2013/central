#include <SFML/Graphics.hpp>
#include "main.h"
#include "test.h"
#include "HScenario.h"
#include "simulation.h"
#include "geography.h"
#include "tilemap.h"
#define DEBUG false
#include "debug.h"

// FIXME we depend on too many other classes
namespace test {
  int pathfinding() {
    std::string seed = "424242";
    auto nbPlayers = 1;
    Geography geo = Generation1(seed);
    Simulation simu = Simulation(&geo,nbPlayers, 1);
    HScenario scenar = HScenario(simu);
    simu.setScenario(&scenar);
    //simu.setClient(clientPtr);
    GraphicContextIso graContIso = GraphicContextIso(&geo, &simu);
    TileMap tilemap = TileMap(&simu, &geo);
    graContIso.load();
    std::default_random_engine npcGen (42);
    dummy::createNPCs(1, simu, graContIso, geo, npcGen);
    LOG(info) << "Finished test NPCs creation and pathfinding";
    return 0;
  }
}
