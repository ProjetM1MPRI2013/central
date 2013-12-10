#include "geography.h"
#include "tile.h"

#define DEBUG true


Geography::Geography(std::string seed){
  //new Generation1(seed); ?? Generation1 inherits from Geography
}

float Geography::getAnxiety(int i, int j){

	return ((this->map[i][j])->getAnxiety());
}


void Geography::setAnxiety(int i, int j, float anxiety){
	map[i][j]->setAnxiety(anxiety);
	return;
}

Tile * Geography::getTile(int i,int j){
	return (map[i][j]);
}

Tile& Geography::getTileRef(int i,int j){
	return *(map[i][j]);
}


int Geography::getMapWidth(){
  return(MAP_WIDTH);
}

int Geography::getMapHeight(){
  return(MAP_HEIGHT);
}

size_t Geography::hachage(std::string seed) { 
  return 0;
}
void Geography::fillBuildings(int abs0, int ord0, int abs1, int ord1, int seed, int nbLine, std::string file) { 
  return;
}


void Geography::printMatrix(){
  if (DEBUG) {std::cout << "Print Matrix" << std::endl;}
  for (int i = 0; i < this->MAP_WIDTH; i++){
    if (DEBUG) {std::cout << "i: " << i << std::endl;}
    for (int j = 0; j < this->MAP_HEIGHT; j++){
      if (DEBUG) {std::cout << "j: " << j << std::endl;}
      std::cout << "\t";
      if (this->getTile(i,j) == 0){std::cout << "VOID ";}
      else {this->getTile(i,j)->printTileType();}
      //else {std::cout << this->getTile(i,j)->getType() << std::endl;}
    }
    std::cout << std::endl;
  }
};
