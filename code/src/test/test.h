#ifndef TEST_H
#define TEST_H
#include "test_pathfinding.h"
#include "test_interface_init.h"
#include "test_generation.h"
#include "test_localstate.h"
#include "test_terroview.h"
#include "test_mayorview.h"
#include "test_scenario.h"
#include "test_net.h"
namespace test {
  int run ();
  int run (std::string which);
  int sfml();
}
#endif
