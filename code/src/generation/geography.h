#ifndef GEOGRAPHY
#define GEOGRAPHY

class Tile;

class Geography {
 private :
  static const int MAP_SIZE  = 100;
  Tile* map[MAP_SIZE][MAP_SIZE];
	
 public :
  /**
   * @brief Génération aléatoire d'une map à partir d'une seed
   * @param seed: paramètre de la génération de la map
   */
  Geography(int seed);
  void setAnxiety(int i, int j, float anxiety);
  float getAnxiety(int i, int j);
  Tile* getTile(int i,int j);
  Tile& getTileRef(int i,int j);
  
}
;

#endif // GEOGRAPHY_H
