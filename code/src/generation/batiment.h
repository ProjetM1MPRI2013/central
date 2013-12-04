#ifndef BATIMENT_H
#define BATIMENT_H

#include <fstream>
#include <assert.h> 
#include <string>
#include "tile.h"

/**
 * @brief gives the caracteristic of a building and its sprite
 */
class Batiment {

 private: 
  TileType type;
  int weight;
  int lenght;
  float speed[][];
  std::string filePictures;
  Coordinates* picture;

 public:
  /**
   * @brief create a Batiment with the caracteristics put in a file, using the good line
   * @param file : the file where the buildings caracteristics are
   * @param line : the line of the file we have to see for this building
   */ 
  Batiment(std::string file, int line);
  
  TileType getType();
  int getWeight();
  int getLenght();
  float[][] getSpeed();
  std::string getFilePictures();
  Coordinates* getPicture();
  
  

}
;


#endif // BATIMENT_H
