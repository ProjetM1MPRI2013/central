#include <SFML/Graphics.hpp>
#include "main.h"
#include "test.h"
#define DEBUG false
#include "debug.h"

namespace test {
int run() {
  LOG(error) << "Not implemented yet. This should run all tests.";
  return 1;
}

int run(std::string which)
{
  if (which == "sfml") {
    return sfml();
  } else if (which == "net") {
    return net_serialization() || net_dummy() || net_real() ;
  } else if (which == "interface_init") {
    return interface_init();
  } else if (which == "pathfinding") {
    return pathfinding();
  } else if (which == "generation") {
    return generation();
  } else if (which == "scenario") {
    return scenario();
  } else if (which == "localstate") {
    return localstate();
  } else if (which == "globalstate") {
    return globalstate();
  } else if (which == "terroview") {
    return terroview();
  } else if (which == "mayorview") {
    return mayorview();
  } else if (which == "events") {
    return events();
  } else if (which == "misc") {
    return misc();
  } else {
    LOG(error) << "Unknown test : " << which;
  }
  return 1;
}

int sfml() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
}
