#ifndef GEOGRAPHY
#define GEOGRAPHY

#include <string>
#include "tile.h"
#include <SFML/Graphics.hpp>

class Tile;

class Geography {
 private :
  static const int MAP_WIDTH  = 100;
  static const int MAP_HEIGHT = 100;
  Tile* map[MAP_WIDTH][MAP_HEIGHT];

 protected:
  virtual size_t hachage(std::string seed);
  virtual void fillBuildings(int abs0, int ord0, int abs1, int ord1);
	
 public :
  /**
   * @brief Génération aléatoire d'une map à partir d'une seed
   * @param seed: paramètre de la génération de la map
   */
  Geography(std::string seed);
  void setAnxiety(int i, int j, float anxiety);
  float getAnxiety(int i, int j);
  Tile* getTile(int i,int j);
  Tile& getTileRef(int i,int j);
  int getMapHeight();
  int getMapWidth();
  
}
;

#endif // GEOGRAPHY_H
