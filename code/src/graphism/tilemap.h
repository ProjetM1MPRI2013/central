#ifndef TILEMAP
#define TILEMAP
#include <TGUI/TGUI.hpp>
#include <iostream>
// #include <string.hpp>
#include <sstream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "../network/network.h"
#include "../network/netEvent.h"
#include <chat_event.h>
#include "../generation/geography.h"
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
  TileMap(Simulation* simu, Geography* geo);
  bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
  void run(sf::RenderWindow* window);
private:
  int Tilesbite[10000];
  Simulation* simu;
  Geography* geo;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  void createTiles();
  sf::VertexArray m_vertices;
  sf::Texture m_tileset;
};

#endif
