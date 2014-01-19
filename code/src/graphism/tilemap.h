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
#include "simulation.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
  TileMap(Simulation* glob, Geography* geo);
  bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
  void setZoom(int resize);
  int getZoom();
  void setCoord(int x,int y);
  int getX();
  int getY();

  // resize = le niveau actuel de zoom
  void run(sf::RenderWindow* window);
private:
  //les coordonnées du point en haut à gauche. 0,0 veut dire le bord du haut à gauche de l'écran est le bord du haut à gauche de l'écran
  int x = 0,y = 0;
  int zoom;
  int Tilesbite[10000];
  Simulation* glob;
  Geography* geo;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  void createTiles();
  sf::VertexArray m_vertices;
  sf::Texture m_tileset;
};

#endif
