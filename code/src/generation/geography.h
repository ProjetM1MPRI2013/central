#ifndef GEOGRAPHY
#define GEOGRAPHY

#include <string>
#include "tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cerrno>

class Tile;

/**
 * @brief this class creates the map of the game
 * the maps are randomly generated
 * we want to implement different methods of generation, so we use inherited classes
 */
class Geography {

 protected:
  /**
   * Height of the map
   */
  static const int MAP_HEIGHT = 100;
  /**
   * Width of the map
   */
  static const int MAP_WIDTH = 100;
  /**
   * The map, which is a matrix of tiles
   */
  Tile* map[MAP_HEIGHT][MAP_WIDTH];
  /**
   * @brief transform the seed in int to be used in the generation algorithm
   * @param seed : a string given a player, to create a random map
   * @return a int used to initialize the pseudo-random suite
   */
  virtual std::size_t hachage(std::string seed);
  /**
   * @brief puts some buildings in a rectangular aera
   * @param abs0 : abscissa of the left of the rectangular
   * @param ord0 : ordinate of the up of the rectangular
   * @param abs1 : abscissa of the right of the rectangular
   * @param ord1 : ordinate of the bottom of the rectangular
   * @param seed : random value used to initialize a new pseudo-random suite used for choosing the building 
   * @param nbLine : number of line of the file with the differents building we can use
   * @param file : name of the file with the differents building we can use
   */
  virtual void fillBuildings(int abs0, int ord0, int abs1, int ord1, int seed, int nbLine, std::string file);
	
 public :
  /**
   * @brief Génération aléatoire d'une map à partir d'une seed
   * @param seed: paramètre de la génération de la map
   */
  Geography(std::string seed);
  /**
   * @brief Sets the anxiety in a particular tile
   * @param i : abscissa of the tile
   * @param j : ordinate of the tile
   * @param anxiety : the new anxiety of the tile
   */
  void setAnxiety(int i, int j, float anxiety);
  /**
   * @brief gives the anxiety of a tile
   * @param i : abscissa of the tile
   * @param j : ordinate of the tile
   * @return the anxiety of the tile
   */
  float getAnxiety(int i, int j);
  /**
   * @brief gives a tile of the map caracterized by these coordinates
   * @param i : abscissa of the tile
   * @param j : ordinate of the tile
   * @return a pointer to the tile
   */
  Tile* getTile(int i,int j);
  /**
   * @brief gives a tile of the map caracterized by these coordinates
   * @param i : abscissa of the tile
   * @param j : ordinate of the tile
   * @return a ref of the tile
   */
  Tile& getTileRef(int i,int j);
  /**
   * @brief gives the width of the map
   * @return the width of the map
   */
  int getMapWidth();
  /**
   * @brief gives the height of the map
   * @return the height of the map
   */
  int getMapHeight();
  

  void printMatrix();
}
;

#endif // GEOGRAPHY_H
