#ifndef BATIMENT
#define BATIMENT

/**
 * @brief gives the caracteristic of a building and its sprite
 */
class Batiment {

 private: 
  TileType type;
  int weight;
  int lenght;
  float speed[][];
  string filePictures;
  Coordinates picture;

 public:
  /**
   * @brief create a Batiment with the caracteristics put in a file, using the good line
   * @param file : the file where the buildings caracteristics are
   * @param line : the line of the file we have to see for this building
   */ 
  Batiment(string file, int line);
  
  TileType getType();
  int getWeight();
  int getLenght();
  float[][] getSpeed();
  string getFilePictures();
  Coordinates getPicture();
  
  

}
;


#endif // BATIMENT_H
