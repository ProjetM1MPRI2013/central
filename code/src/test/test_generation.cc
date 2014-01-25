#include <SFML/Graphics.hpp>
#include "main.h"
#include "test.h"
#include "HScenario.h"
#include "localState.h"
#include "geography.h"
#include "tilemap.h"
#define DEBUG false
#include "debug.h"

namespace test {
  int generation() {
    std::string seed = "424242";
    Generation1{seed};
    return 0;
  }
}
