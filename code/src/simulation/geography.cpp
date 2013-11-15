#include "geography.h"

float Geography::getAnxiety(int i, int j){
	return (map[i][j].getAnxiety());
}

void Geography::setAnxiety(int i, int j, float anxiety){
	map[i][j].setAnxiety(anxiety);
	return;
}

Tile& Geography::getTile(int i,int j){
	return (map[i][j]);
}
