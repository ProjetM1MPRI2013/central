#include <SFML/Graphics.hpp>
#include "main.h"
#include "test.h"
#include "test_misc.h"
#include "localState.h"
#include "geography.h"
#include "tilemap.h"
#define DEBUG false
#include "debug.h"
#include <boost/uuid/string_generator.hpp>

namespace test {
  int misc() {
    std::string seed = "424242";
    Geography geo = Generation1("424242");
    LocalState loc = LocalState(&geo,1, 1);

    float xPosition = 2.3;
    boost::uuids::string_generator generator;
    boost::uuids::uuid uuid = generator("{01234567-89ab-cdef-0123-456789abcdef}");

    loc.addNPC(Position(xPosition,0),Position(xPosition,0),0,nullptr,uuid);
    NPC* foundNPC = loc.getNPCByID(uuid);

    assert(foundNPC != nullptr);
    assert(foundNPC->position.getX() == xPosition);
    return 0;
  }
}
