#include "generation1.h"
#include <boost/functional/hash.hpp>
#include "tile.h"
#include <cstdlib>
#include <string>

Generation1::Generation1 (std::string seed) : Geography(seed) {
  //int MAP_HEIGHT = 100;
  //int MAP_WIDTH = 100;
  std::size_t seed1 = hachage(seed);
  srand(int(seed1));
  int maxInter, minInter, nbInter1, nbInter2, nbRand, nbLine;
  std::string file = "../graphim/buildings";
  std::string ligne;
  std::fstream fichier;
  fichier.open(file, std::fstream::in);
  assert(fichier);
  nbLine = 0;
  while(getline(fichier, ligne)){
    nbLine++;
  }
  fichier.close();
  maxInter = 6;
  minInter = 2;
  nbInter1 = 0;
  nbInter2 = 0;
  while (nbInter1 < minInter) {
    nbRand = rand();
    nbInter1 = nbRand % maxInter;
  }
  while (nbInter2 < minInter)  {
    nbRand = rand();
    nbInter2 = nbRand % maxInter;
  }
  Batiment batiment; 
  int heightInter, widthInter, choose, poids, widthRoadh, heightRoadv;
  poids = -1;
  // On choisit le type d'intersection que l'on va utiliser de maière aléatoire, à l'aide d'un poids donner à chaque intersection
  int i, j, i2, j2;
  for(i=1; i<=nbLine; i++) {
    batiment = Batiment(file, i);
    if(batiment.getType()==INTER) {
      nbRand = rand();
      if (nbRand > poids) {choose = i; poids = nbRand;}
    }
  }
  Batiment intersection = Batiment(file, choose);
  heightInter = intersection.getHeight();
  widthInter = intersection.getWidth();
  // On choisit une sprite de route horizontale avec la bonne largeur
  for(i=1; i<=nbLine; i++) {
    batiment = Batiment(file, i);
    if(batiment.getType()==ROADH && batiment.getHeight() == heightInter) {
      nbRand = rand();
      if (nbRand > poids) {choose = i; poids = nbRand;}
    }
  }
  Batiment roadh = Batiment(file, choose);
  widthRoadh = roadh.getWidth();
  // On choisit une sprite de route verticale avec la bonne longueur
  for(i=1; i<=nbLine; i++) {
    batiment = Batiment(file, i);
    if(batiment.getType()==ROADV && batiment.getWidth() == widthInter) {
      nbRand = rand();
      if (nbRand > poids) {choose = i ; poids = nbRand;}
    }
  }
  Batiment roadv = Batiment(file, choose);
  heightRoadv = roadv.getHeight();
  int absInter[nbInter1];
  int ordInter[nbInter2];
  int min, max;
  min = 0;
  max = MAP_WIDTH - nbInter1*widthInter;
  for (i=0; i<nbInter1; i++) {
    nbRand = rand();
    nbRand = nbRand % (max-min+1);
    while(nbRand % widthRoadh != 0){
      nbRand = rand();
      nbRand = nbRand % (max-min+1);
    }
    absInter[i] = nbRand + min;
    min = absInter[i] + widthInter;
    max = max - widthInter;
  }
  min = 0;
  max = MAP_HEIGHT - nbInter2*heightInter;
  for (j=0; j<nbInter2; j++) {
    nbRand = rand();
    nbRand = nbRand % (max-min+1);
    while(nbRand % heightRoadv != 0){
      nbRand = rand();
      nbRand = nbRand % (max-min+1);
    }
    ordInter[j] = nbRand + min;
    min = ordInter[j] + heightInter;
    max = max - heightInter;
  }
  int abs0, ord0, abs1, ord1, abs2, ord2;
  abs0 = 0;
  ord0 = 0;
  for (i=0; i<=nbInter1; i++) {
    if(i<nbInter1) {
      abs1 = absInter[i] ;
	}
    else {
      abs1 = MAP_WIDTH-1;
    }
    for (j=0; j<nbInter2; j++) {
      ord1 = ordInter[j];
      fillBuildings(abs0, ord0, abs1, ord1, nbRand, nbLine, file);
      ord2 = ord0;
      if(i<nbInter1){
	while(ord2<ord1){
	  for(i2=0; i2<widthInter; i2++){
	    for(j2=0; j2<heightRoadv; j2++) {
	      if(i2==0){this->map[abs1+i2][ord2+j2] = new Tile(abs0+i2, ord2+j2, ROADV, false, float(0.), float(1.), true, true, true, false, float(1.), Coordinates(abs0,ord2), Coordinates(0,0), NULL);}
	      else if(i2==(widthInter-1)){this->map[abs1+i2][ord2+j2] = new Tile(abs0+i2, ord2+j2, ROADV, false, float(0.), float(1.), true, true, false, true, float(1.), Coordinates(abs0,ord2), Coordinates(0,0), NULL);}
	      else {this->map[abs1+i2][ord2+j2] = new Tile(abs0+i2, ord2+j2, ROADV, false, float(0.), float(1.), true, true, true, true, float(1.), Coordinates(abs0,ord2), Coordinates(0,0), NULL);}
	    }
	  }
	  ord2 = ord2 + widthInter;
	}
      }
      abs2 = abs0;
      while(abs2<abs1){
	for(i2=0; i2<widthRoadh; i2++){
	  for(j2=0; j2<heightInter; j2++) {
	    if(j2==0){this->map[abs1+i2][ord2+j2] = new Tile(abs2+i2, ord0+j2, ROADH, false, 0., 1., false, true, true, true, float(1.), Coordinates(abs2,ord0), Coordinates(0,0), NULL);}
	    else if(j2 ==(heightInter - 1)){this->map[abs1+i2][ord2+j2] = new Tile(abs2+i2, ord0+j2, ROADH, false, 0., 1., true, false, true, true, float(1.), Coordinates(abs2,ord0), Coordinates(0,0), NULL);}
	    else {this->map[abs1+i2][ord2+j2] = new Tile(abs2+i2, ord0+j2, ROADH, false, 0., 1., true, true, true, true, float(1.), Coordinates(abs2,ord0), Coordinates(0,0), NULL);}
	  }
	}
	abs2 = abs2 + heightInter;
      }
      if(i<nbInter1) {
	for(i2=0; i2<widthInter; i2++){
	  for(j2=0; j2<heightInter; j2++) {
	    this->map[abs1+i2][ord1+j2] = new Tile(abs2+i2, ord0+j2, INTER, false, 0., 1., true, true, true, true, float(1.),  Coordinates(abs1,ord1),  Coordinates(0,0), NULL);
	  }
	}
      }
      abs0 = abs1;
      ord0 = ord1;
    }
    ord1 = MAP_HEIGHT - 1;
    fillBuildings(abs0, ord0, abs1, ord1, nbRand, nbLine, file);
    ord2 = ord0;
    while(ord2<ord1){
      for(i2=0; i2<widthInter; i2++){
	for(j2=0; j2<heightRoadv; j2++) {
	  if(i2==0){this->map[abs1+i2][ord2+j2] = new Tile(abs0+i2, ord2+j2, ROADV, false, float(0.), float(1.), true, true, true, false, float(1.), Coordinates(abs0,ord2), Coordinates(0,0), NULL);}
	  else if(i2==(widthInter-1)){this->map[abs1+i2][ord2+j2] = new Tile(abs0+i2, ord2+j2, ROADV, false, float(0.), float(1.), true, true, false, true, float(1.), Coordinates(abs0,ord2), Coordinates(0,0), NULL);}
	  else {this->map[abs1+i2][ord2+j2] = new Tile(abs0+i2, ord2+j2, ROADV, false, float(0.), float(1.), true, true, true, true, float(1.), Coordinates(abs0,ord2), Coordinates(0,0), NULL);}
	}
      }
    }
    
  }
}

std::size_t Generation1::hachage(std::string seed) {
  boost::hash<std::string> string_hash;
  std::size_t seed1;
  seed1 = string_hash(seed);
  return(seed1);
}



void Generation1::fillBuildings(int abs0, int ord0, int abs1, int ord1, int seed, int nbLine, std::string file) {
  int nbRand, i, j;
  int poidsBank = 100;
  int poidsHouse = 150;
  srand(nbRand);
  int choose = 0;
  int poids = -1;
  Batiment batiment; 
  for(i=1; i<=nbLine; i++) {
    batiment = Batiment(file, i);
    if(batiment.getType()==BANK && batiment.getHeight() <= (ord1 - ord0 + 1) && batiment.getWidth() <= (abs1 - abs0 + 1)) {
      nbRand = rand();
      nbRand = nbRand % poidsBank;
      if (nbRand > poids) {choose = i; poids = nbRand;}
    }
    if(batiment.getType()==HOUSE && batiment.getHeight() <= (ord1 - ord0 + 1) && batiment.getWidth() <= (abs1 - abs0 + 1)) {
      nbRand = rand();
      nbRand = nbRand % poidsHouse;
      if (nbRand > poids) {choose = i; poids = nbRand;}
    }
  }
  if(choose==0){
    for(i=abs0; i<abs1; i++){
      for(j=ord0; j<ord1; j++){
	this->map[i][j] = new Tile(i,j,TileType::BLANK,false, 0., 0., false, false, false, false, 0., Coordinates(abs0, ord0), Coordinates(0,0), NULL);
      }
    }
  }
  else {
    batiment = Batiment(file, choose);
    int width = batiment.getWidth();
    int height = batiment.getHeight();
    for(i=abs0; i<abs0 + width ; i++){
      for(j=ord0; j<ord1 + height; j++){
	this->map[i][j] = new Tile(i,j,batiment.getType(),false, 0., 0., false, false, false, false, 0., Coordinates(abs0, ord0), Coordinates(0,0), NULL);
      }
    }
    fillBuildings(abs0 + width, int(ord0), int(abs1), int(ord1), int(nbRand), int(nbLine), std::string(file));
    fillBuildings(abs0, ord0 + height, abs0 + width -1 , ord1, nbRand, int(nbLine), file);
  }
  return;
}
