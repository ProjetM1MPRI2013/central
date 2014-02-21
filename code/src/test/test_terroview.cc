//@author: Adrien H.
#include <SFML/Graphics.hpp>
#include "main.h"
#include "test.h"
#include "HScenario.h"
#include "localState.h"
#include "geography.h"
#define DEBUG false
#include "debug.h"

namespace test {
  int terroview() {
    std::string seed = "424242";
    auto nbPlayers = 1;
    Geography geo = Generation1(seed);
    LocalState loc = LocalState(&geo,nbPlayers, 1);
    HScenario scenar = HScenario(loc);
    loc.setScenario(&scenar);
    GraphicContextIso graContIso = GraphicContextIso(&geo, &loc);
    return 0;
  }
}
