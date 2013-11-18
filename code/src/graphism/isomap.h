#ifndef ISOMAP
#define ISOMAP

#include <SFML/Graphics.hpp>
#include <simulation/localState.h>

#define RIGHT_TILE = [20;-10] /* Distance à la tile de droite */
#define DOWN_TILE = [20;11] /* Distance à la tile du bas */

struct coord :
{ 
  int x , y;
};

class Sprite :
{
 public:
  int getHeight();
  int getWidth();
  coord getTile();
  coord getMap();
  void setHeight(int h);
  void setWidth(int w);
  void setTile(coord ct);
  void setMap(coord cm);

 private:
  int height, width;
  coord c_tileset, c_map; 
  // c_tileset : coordonnées dans la tileset
  // c_map : coordonnées dans la sprite qui correspondent à l'origine sur la map.

};
  

class IsoMap : public sf::Drawable, public sf::Transformable
{
 public:
  bool load(const std::string& tileset, const Terrain* tiles);
 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  sf::VertexArray m_vertices;
  sf::Texture m_tileset;
};



#endif
