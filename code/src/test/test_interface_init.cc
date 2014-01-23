#include <SFML/Graphics.hpp>
#include "test_interface_init.h"
#include "interfaceinit/interface_init.h"

#define DEBUG false
#include "debug.h"

namespace test {
  int interface_init()
  {
    LOG(debug) << "TEST INTERFACE INIT";
    int sizeFenetre[3];
    bool isFullScreen;
    sf::VideoMode video_mode;
    interface_initiale(sizeFenetre, &isFullScreen);
    return 0;
  }
}
