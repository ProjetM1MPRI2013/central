#include "geography.h"
#include "tile.h"



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
void Geography::fillBuildings(int abs0, int ord0, int abs1, int ord1) { 
  return;
}
