#ifndef GEOGRAPHY
#define GEOGRAPHY

#include <string>
#include "tile.h"
#include <SFML/Graphics.hpp>

class Tile;

class Geography {

 protected:
  static const int MAP_HEIGHT = 100;
  static const int MAP_WIDTH = 100;
  Tile* map[MAP_HEIGHT][MAP_WIDTH];
  virtual std::size_t hachage(std::string seed);
  virtual void fillBuildings(int abs0, int ord0, int abs1, int ord1, int seed, int nbLine, std::string file);
	
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
  int getMapWidth();
  int getMapHeight();
  
}
;

#endif // GEOGRAPHY_H
