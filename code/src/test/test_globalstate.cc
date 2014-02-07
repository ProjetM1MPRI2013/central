#include <SFML/Graphics.hpp>
#include "main.h"
#include "test.h"
#include "HScenario.h"
#include "globalState.h"
#include "geography.h"
#include "tilemap.h"
#define DEBUG false
#include "debug.h"

namespace test {
  int globalstate() {
    std::string seed = "424242";
    auto nbPlayers = 1;
    Geography geo = Generation1(seed);
    LOG(debug) << "address of geo " << &geo;
    GlobalState glob = GlobalState(&geo,nbPlayers, 1);
    LOG(debug) << "address of map in LocalState " << glob.getMap();
    LOG(info) << "Global State testing done.";

    return 0;
  }
}
