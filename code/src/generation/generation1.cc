#include "generation1.h"
#include <boost/functional/hash.hpp>
#include "tile.h"
#include <cstdlib>
#include <string>

Generation1::Generation1(string seed){
  size_t seed1 = hachage(seed);
  int maxInter, minInter, nbInter1, nbInter2, nbRand, nbLine;
  string file = "../graphim/buildings";
  string ligne;
  fstream fichier;
  fichier.open(file, std::fstream::in);
  assert(fichier);
  nbLine = 0;
  while(getline(fichier, ligne)){
    nbLine++;
  }
  fichier.close();
  srand(int(seed));
  maxInter = 6;
  minInter = 2;
  nbInter1 = 0;
  nbInter2 = 0;
  while nbInter1 < minInter do {
      nbRand = rand();
      nbInter1 = nbRand % maxInter;
    }
  while nbInter2 < minInter do {
      nbRand = rand();
      nbInter2 = nbRand % maxInter;
    }
  Batiment batiment;
  int weightInter, lenghtInter, choose, poids, lenghtRoadh, weightRoadv;
  poids = -1;
  // On choisit le type d'intersection que l'on va utiliser de maière aléatoire, à l'aide d'un poids donner à chaque intersection
  for(i=1; i<=nbLine; i++) {
    batiment = new Batiment(file, i);
    if(batiment.getType()==INTER) {
      nbRand = rand();
      if (nbRand > poids) {choose = i}
    }
  }
  Batiment intersection = new Batiment(file, choose);
  weightInter = intersection.getWeight();
  lenghtInter = intersection.getLenght();
  // On choisit une sprite de route horizontale avec la bonne largeur
  for(i=1; i<=nbLine; i++) {
    batiment = new Batiment(file, i);
    if(batiment.getType()==ROADH && batiment.getWeight() == weightInter) {
      nbRand = rand();
      if (nbRand > poids) {choose = i}
    }
  }
  Batiment roadh = new Batiment(file, choose);
  lenghtRoadh = roadh.getLenght();
  // On choisit une sprite de route verticale avec la bonne longueur
  for(i=1; i<=nbLine; i++) {
    batiment = new Batiment(file, i);
    if(batiment.getType()==ROADV && batiment.getLenght() == lenghtInter) {
      nbRand = rand();
      if (nbRand > poids) {choose = i}
    }
  }
  Batiment roadv = new Batiment(file, choose);
  weightRoadv = roadv.getWeight();
  int absInter[nbInter1];
  int ordInter[nbInter2];
  int min, max;
  min = 0;
  max = MAX_LENGHT - nbInter1*lenghtInter;
  for (i=0; i<nbInter1; i++) {
    nbRand = rand();
    nbRand = nbRand % (max-min+1);
    while(nbRand % lenghtRoadh != 0){
      nbRand = rand();
      nbRand = nbRand % (max-min+1);
    }
    absInter[i] = nbRand + min;
    min = absInter[i] + lenghtInter;
    max = max - lenghtInter;
  }
  min = 0;
  max = MAX_WEIGHT - nbInter2*weightInter;
  for (j=0; j<nbInter2; j++) {
    nbRand = rand();
    nbRand = nbRand % (max-min+1);
    while(nbRand % weightRoadv != 0){
      nbRand = rand();
      nbRand = nbRand % (max-min+1);
    }
    ordInter[j] = nbRand + min;
    min = ordInter[j] + weightInter;
    max = max - weightInter;
  }
  int abs0, ord0, abs1, ord1, abs2, ord2;
  abs0 = 0;
  ord0 = 0;
  for (i=0; i<=nbInter1; i++) {
    if(i<nbInter1) {
      abs1 = absInter[i]
	}
    else {
      abs1 = MAX_LENGHT-1;
    }
    for (j=0; j<nbInter2; j++) {
      ord1 = ordInter[j];
      fillBuildings(abs0, ord0, abs1, ord1);
      ord2 = ord0;
      if(i<nbInter1){
	while(ord2<ord1){
	  for(i2=0; i2<lenghtRoadv; i2++){
	    for(j2=0; j2<weightInter; j2++) {
	      map[abs1+i2][ord2+j2] = new Tile(abs0+i2, ord2+j2, ROADV, false, 0., 1., 1,1,1,1,new Coordinates(abs0,ord2), new Coordinates(0,0));
	    }
	  }
	  ord2 = ord2 + lenghtInter;
	}
      }
      abs2 = abs0;
      while(abs2<abs1){
	for(i2=0; i2<lenghtInter; i2++){
	  for(j2=0; j2<weighRoadh; j2++) {
	    this->map[abs1+i2][ord2+j2] = new Tile(abs2+i2, ord0+j2, ROADH, false, 0., 1., 1,1,1,1,new Coordinates(abs2,ord0), new Coordinates(0,0));
	  }
	}
	abs2 = abs2 + weightInter;
      }
      if(i<nbInter1) {
	for(i2=0; i2<lenghtInter; i2++){
	  for(j2=0; j2<weighInter; j2++) {
	    this->map[abs1+i2][ord1+j2] = new Tile(abs2+i2, ord0+j2, INTER, false, 0., 1., 1,1,1,1,new Coordinates(abs1,ord1), new Coordinates(0,0));
	  }
	}
      }
      abs0 = abs1;
      ord0 = ord1;
    }
    ord1 = MAP_WEIGHT - 1;
    fillBuildings(abs0, ord0, abs1, ord1);
    ord2 = ord0;
    while(ord2<ord1){
      for(i2=0; i2<lenghtRoadv; i2++){
	for(j2=0; j2<weightInter; j2++) {
	  this->map[abs1+i2][ord2+j2] = new Tile(abs0+i2, ord2+j2, ROADV, false, 0., 1., 1,1,1,1,new Coordinates(abs0,ord2), new Coordinates(0,0));
	}
      }
    }
    
  }
}

std::size_t Generation1::hachage(string seed) {
  boost::hash<std::string> string_hash;
  std::size_t seed1;
  seed1 = string_hash(seed);
  return(seed1);
}


void Generation1::fillBuildings(int abs0, int ord0, int abs1, int ord1) {
  // On commence par une version débile en mettant des cases BLANK partout
  for(i=abs0; i<abs1; i++){
    for(j=ord0; j<ord1; j++){
      this->map[i][j] = new Tile(i,j,BLANK,false, 0., 0., 0,0,0,0,new Coordinates(abs0, ord0), new Coordinates(0,0));
    }
  }
}
