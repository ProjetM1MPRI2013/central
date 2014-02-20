#ifndef BATIMENT_H
#define BATIMENT_H

#include <fstream>
#include <assert.h> 
#include <iostream>
#include <string>
#include "tile.h"

// Une matrice de floats (float[][] oblige à déclarer une dimension max. sur les colonnes)
typedef std::vector<std::vector<float>> floatMatrix;

/**
 * @brief gives the caracteristic of a building and its sprite
 * @author: ChatanW
 */
class Batiment {

 private: 
  /**
   * the type of the building, one of the enum
   */
  TileType type;
   /**
   * the height of the building
   */
  int height;
  /**
   * the width of the building
   */
  int width;
  /**
   * the mask of speed of the building, each tile can have a different factor for the speed of the perso
   */
  floatMatrix speed;
  /**
   * the name of the file where the sprite of the building is
   */
  std::string filePictures;
  /**
   * the position of the sprite of the building in the file
   */
  Coordinates picture;

 public:
  /**
   * @brief create a Batiment with the caracteristics put in a file, using the good line
   * @param file : the file where the buildings caracteristics are
   * @param line : the line of the file we have to see for this building
   */ 
  Batiment(std::string file, int line);

  /**
   * @brief create a NULL Batiment
   */
  Batiment();

  /**
   * @brief gives the type of the building
   * @return the type, one of the enum
   */
  TileType getType();
  /**
   * @brief gives the height of the building
   * @return the height of the building
   */
  int getHeight();
  /**
   * @brief gives the width of the building
   * @return the width of the building
   */
  int getWidth();
  /**
   * @brief gives the mask of speed of the building
   * @return the mask of speed of the building, each tile can have a different factor for the speed of the perso
   */
  floatMatrix getSpeed();
  /**
   * @brief gives the name of the file where the sprite of the building is
   * @return the name of the file where the sprite of the building is
   */
  std::string getFilePictures();
  /**
  * @brief gives the position of the sprite of the building in the file
  * @return the position of the sprite of the building in the file
  */
  Coordinates getPicture();
  
  

}
;


#endif // BATIMENT_H
