#ifndef GENERATION1
#define GENERATION1

#include "geography.h"
#include <string>
#include <fstream>
#include "batiment.h"
#include <iostream>


/**
 * @brief this class implements a first random generation of a map
 * Geography must generate a map but like we want to have different methods of generation, we use inherited class
 * @commentperso Here, we use a simple method of generation. We obtain a grid of roads with buildins to fill the blanks. It seems like a American city.
 * @author: ChatanW
 */
class Generation1 : public Geography
{

 public:
  /**
   * @brief first method of random map generation
   * the map seems to be the map of a US city
   * the streets form a grid
   * each rectangular is filled independly of the others with the method fillBuidings
   */
  Generation1(std::string seed);
  std::size_t hachage(std::string seed);
    
 private:
  /**
   * @brief puts some buildings in a rectangular aera
   * it begins by the corner up-left and it's recursive
   * when we don't have enough place to put a real building (house or bank), ie the rectangular is smaller than every buiding, we put BLANK tiles
   * @param abs0 : abscissa of the left of the rectangular
   * @param ord0 : ordinate of the up of the rectangular
   * @param abs1 : abscissa of the right of the rectangular
   * @param ord1 : ordinate of the bottom of the rectangular
   * @param seed : random value used to initialize a new pseudo-random suite used for choosing the building 
   * @param nbLine : number of line of the file with the differents building we can use
   * @param file : name of the file with the differents building we can use
   */
  void fillBuildings(int abs0, int ord0, int abs1, int ord1, int seed, int nbLine, std::string file);

  /**
   * @brief At the end of the generation, it may still exist NULL tiles, so we fill them
   * Here, we fill them with BLANK tiles and the choices of the sprite are independant one with another
   * @param seed : random value used to choose the sprite
   * @param nbLine : number of line of the file with the differents building we can use
   * @param file : name of the file with the differents building we can use
   * @comment This method is usefull if the lenght of the sprite of the road is not a divisor of the width or the height of the map
   */
  void fillNull(int seed, int nbLine, std::string file);
};



#endif // GENERATION1_H
