#ifndef GEOGRAPHY
#define GEOGRAPHY

#include <string>
#include "tile.h"

class Geography {
 private :
  static const int MAP_LENGHT  = 100;
  static const int MAP_WEIGHT = 100;
  Tile* map[MAP_LENGHT][MAP_WEIGHT];

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
  int getMapLenght();
  int getMapWeight();
  
}
;

#endif // GEOGRAPHY_H
