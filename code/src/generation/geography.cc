#include "geography.h"
#include "tile.h"



Geography::Geography(string seed){
  new Generation1(seed);
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

int Geography::getMapLenght(){
  return(MAP_LENGHT);
}

int Geography::getMapWeight(){
  return(MAP_WEIGHT);
}
