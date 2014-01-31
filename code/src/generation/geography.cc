#include "geography.h"
#include "tile.h"
#include <assert.h>

#define DEBUG false


Geography::Geography(std::string seed) {
  //new Generation1(seed); ?? Generation1 inherits from Geography
  for (int i=0;i<MAP_WIDTH;i++) {
    for (int j=0;j<MAP_HEIGHT;j++) {
      map[i][j] = NULL;
    }
    }
  return;
}

Geography::Geography(){
  for (int i=0;i<MAP_WIDTH;i++) {
    for (int j=0;j<MAP_HEIGHT;j++) {
      map[i][j] = NULL;
    }
    }
  return;
}

Geography::Geography(const Geography& mapToBeCopied){
  for (int i=0;i<MAP_WIDTH;i++) {
    for (int j=0;j<MAP_HEIGHT;j++) {
      if (mapToBeCopied.map[i][j] != NULL)
	map[i][j] = new Tile(*mapToBeCopied.map[i][j]);
    }
  }
}

Geography::~Geography() {

  for (int i=0;i<MAP_WIDTH;i++) {
    for (int j=0;j<MAP_HEIGHT;j++) {
      delete map[i][j];
    }
    }

  return;
}

float Geography::getAnxiety(int i, int j){
	return ((this->map[i][j])->getAnxiety());
}


void Geography::setAnxiety(int i, int j, float anxiety){
	map[i][j]->setAnxiety(anxiety);
	return;
}

Tile* Geography::getTile(int i,int j){
  assert(i>=0 && i<MAP_WIDTH && j>=0 && j<MAP_HEIGHT);
  return (map[i][j]);
}

Tile& Geography::getTileRef(int i,int j){
  if (!(i>=0 && i<MAP_WIDTH && j>=0 && j<MAP_HEIGHT)) {
    printf("getTileRef error : i=%d, j=%d\n",i,j);
  }
  assert(i>=0 && i<MAP_WIDTH && j>=0 && j<MAP_HEIGHT);
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
    //if (DEBUG) {std::cout << "i: " << i << std::endl;}
    for (int j = 0; j < this->MAP_HEIGHT; j++){
      //if (DEBUG) {std::cout << "j: " << j << std::endl;}
      std::cout << "\t";
      if (this->getTile(i,j) == 0){std::cout << "VOID ";}
      else {this->getTile(i,j)->printTileType(); if(DEBUG) {std::cout << this->getTile(i,j)->getGou() << " " << this->getTile(i,j)->getGod() << " " << this->getTile(i,j)->getGor() << " " << this->getTile(i,j)->getGol();}}
      //else {std::cout << this->getTile(i,j)->getType() << std::endl;}
    }
    std::cout << std::endl;
  }
};

/*
 *@brief test for 2 int if the tile is in the map
 */
bool Geography::isInTheMap (int x, int y) {
  return (
	  (x >= 0)
	  && (x < this->getMapWidth())
	  && (y >= 0)
	  && (y < this->getMapHeight())
	  );
};

/*
 *@brief test if a tile is in the map
 */
bool Geography::isInTheMapTile (Tile* zone) {
  int x = (zone->getCoord()).getAbs();
  int y = (zone->getCoord()).getOrd();
  return (
   	  (x >= 0)
	  && (x < this->MAP_WIDTH)
	  && (y >= 0)
	  && (y < this->MAP_HEIGHT)
	  );
};


/*
 * @brief add a tile to the list if it is on a map
 */
void Geography::neighborsaux (int x,int y , std::list<Tile*>* result) {
	if (isInTheMap (x,y)) {
					result->push_front(
						 this->getTile(x,y)
					);
	}
	else {
	  return;
	};

};

/*
 * @brief create the list of tiles witch are at n tile of the tile t0
 */
std::list<Tile*>* Geography::neighbors (int n,Tile* t0) {
	Coordinates c0 = t0->getCoord();
	int x0 = c0.abs ;
	int y0 = c0.ord ;
	std::list<Tile*>* result = new std::list<Tile*> ;
	for (int i = 0 ; i <= n; ++i){
		for (int j = 0  ; j <= n-i; ++j){
			neighborsaux (x0+i,y0+j,result);
			if (i > 0) {
				neighborsaux (x0-i,y0+j,result);
				if (j>0) {neighborsaux(x0-i,y0-j,result);};
			};
			if (j>0) {
				{neighborsaux(x0-i,y0-j,result);};
			}
		};
	};
	return result;
};
