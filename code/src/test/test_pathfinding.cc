//@auhor: Adrien H.
#include <SFML/Graphics.hpp>
#include "main.h"
//#include "test.h"
#include "HScenario.h"
#include "localState.h"
#include "geography.h"
#define DEBUG false
#include "debug.h"

// FIXME we depend on too many other classes
namespace test {
  int pathfinding() {
    std::string seed = "424242";
    auto nbPlayers = 1;
    // FIXME 10000 tiles are created then copied here
    Geography geo = Generation1(seed);
    LocalState loc = LocalState(&geo,nbPlayers, 1);
    HScenario scenar = HScenario(loc);
    loc.setScenario(&scenar);
    //simu.setClient(clientPtr);
    GraphicContextIso graContIso = GraphicContextIso(&geo, &loc);
    //TileMap tilemap = TileMap(&loc, &geo);
    std::default_random_engine npcGen (42);
    dummy::createNPCs(1, loc, geo, npcGen);
    LOG(info) << "Finished test NPCs creation and pathfinding";
    return 0;
  }
}
