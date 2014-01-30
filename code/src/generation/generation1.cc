#include "generation1.h"
#include <boost/functional/hash.hpp>
#include "tile.h"
#include <string>
#include "pseudorandom.h"



#define DEBUG false

Generation1::Generation1 (std::string seed) : Geography(seed) {

  int debugcpt = 0;
  int debugforcpt = 0;
  if (DEBUG) {std::cout << "generation1 : " << ++debugcpt << std::endl;};

  //int MAP_HEIGHT = 100;
  //int MAP_WIDTH = 100;
  std::size_t seed1 = hachage(seed);
  if (DEBUG){std::cout << "seed : " << seed1 << std::endl;}
  PseudoRandom randomGen(seed1);
  //srand(int(seed1));
  int maxInter, minInter, nbInter1, nbInter2, nbRand, nbLine;
  std::string file = "../graphism/buildings";
  std::string ligne;
  std::fstream fichier;
  fichier.open(file, std::fstream::in);
  assert(fichier);
  nbLine = 0;
  while(getline(fichier, ligne)){
    nbLine++;
  }
  if (DEBUG) {std::cout << "generation1 : " << ++debugcpt << std::endl;};
  fichier.close();
  maxInter = 9;
  minInter = 5;
  assert(minInter <= maxInter);
  nbInter1 = 0;
  nbInter2 = 0;
  // On choisit le nombre d'intersections sur l'axe des abscisses
  while (nbInter1 < minInter) {
    nbRand = randomGen.pseudorand();
    if (DEBUG) {std::cout << "nbRand: " << nbRand << std::endl;}
    nbInter1 = (nbRand % maxInter) + 1;
  }
  if (DEBUG) {std::cout << "nbInter1 : " << nbInter1 << std::endl;};
  if (DEBUG) {std::cout << "generation1 : " << ++debugcpt << std::endl;};
  // On choisit le nombre d'intersections sur l'axe des ordonnées
  while (nbInter2 < minInter)  {
    nbRand = randomGen.pseudorand();
    if (DEBUG) {std::cout << "nbRand: " << nbRand << std::endl;}
    nbInter2 = (nbRand % maxInter) + 1;
  }
  if (DEBUG) {std::cout << "nbInter2 : " << nbInter2 << std::endl;};
  if (DEBUG) {std::cout << "generation1 : " << ++debugcpt << std::endl;};
  Batiment batiment; 

  //J'initialise choose a -1 par défault, je ne suis pas sur que cela soit une bonne idée [Adrien K.]
  int choose = 0;

  int heightInter, widthInter, poids, widthRoadV, heightRoadH;
  poids = -1;
  // On choisit le type d'intersection que l'on va utiliser de maière aléatoire, à l'aide d'un poids donner à chaque intersection
  int i, j, i2, j2;
  for(i=0; i < nbLine; i++) {
    if (DEBUG) {std::cout << "generation1 : For : " << ++debugforcpt << std::endl;};
    batiment = Batiment(file, i);
    if(batiment.getType()==INTER) {
      nbRand = randomGen.pseudorand();
      if (DEBUG) {std::cout << "nbRand: " << nbRand << std::endl;}
      if (nbRand > poids) {choose = i; poids = nbRand;}
    }
  }
  if (DEBUG) {std::cout << "generation1 : " << ++debugcpt << std::endl;};
  Batiment intersection = Batiment(file, choose);
  heightInter = intersection.getHeight();
  widthInter = intersection.getWidth();
  std::string fileInter = intersection.getFilePictures();
  if (DEBUG) {std::cout << fileInter << std::endl;}
  Coordinates pictureInter = intersection.getPicture();
  floatMatrix speedInter = intersection.getSpeed();
  if (DEBUG) {std::cout << "heightInter " << heightInter << std::endl;};
  if (DEBUG) {std::cout << "widthInter " << widthInter << std::endl;};
  // On choisit une sprite de route horizontale avec la bonne largeur
  choose = 0;
  poids = -1;
  for(i=0; i<nbLine; i++) {
    batiment = Batiment(file, i);
    if(batiment.getType()==ROADH && batiment.getWidth() == widthInter) {
      nbRand = randomGen.pseudorand();
      if (DEBUG) {std::cout << "nbRand: " << nbRand << std::endl;}
      if (nbRand > poids) {choose = i; poids = nbRand;}
    }
  }
  if (DEBUG) {std::cout << "generation1 : " << ++debugcpt << std::endl;};
  Batiment roadh = Batiment(file, choose);
  heightRoadH = roadh.getHeight();
  std::string fileRoadH = roadh.getFilePictures();
  if (DEBUG) {std::cout << fileRoadH << std::endl;}
  Coordinates pictureRoadH = roadh.getPicture();
  floatMatrix speedRoadH = roadh.getSpeed();
  // On choisit une sprite de route verticale avec la bonne longueur
  choose = 0;
  poids = -1;
  for(i=0; i<nbLine; i++) {
    batiment = Batiment(file, i);
    if(batiment.getType()==ROADV && batiment.getHeight() == heightInter) {
      nbRand = randomGen.pseudorand();
      if (DEBUG) {std::cout << "nbRand: " << nbRand << std::endl;}
      if (nbRand > poids) {choose = i ; poids = nbRand;}
    }
  }
  if (DEBUG) {std::cout << "generation1 : " << ++debugcpt << std::endl;};
  Batiment roadv = Batiment(file, choose);
  widthRoadV = roadv.getWidth();
  std::string fileRoadV = roadv.getFilePictures();
  if (DEBUG) {std::cout << roadv.getType() << std::endl;}
  if (DEBUG) {std::cout << fileRoadV << std::endl;}
  Coordinates pictureRoadV = roadv.getPicture();
  floatMatrix speedRoadV = roadv.getSpeed();

  // On choisit les abscisses et les ordonnées des intersections
  int absInter[nbInter1];
  int ordInter[nbInter2];
  int min, max;
  int nbRand2;
  int seuil1 = 666;
  int seuil2 = 6;
  min = 0;
  max = MAP_WIDTH - nbInter1*widthInter;
  if (DEBUG) {std::cout << "min : " << min << std::endl;}
  if (DEBUG) {std::cout << "max : " << max << std::endl;}
  for (i=0; i<nbInter1; i++) {
    nbRand = randomGen.pseudorand();
    if (DEBUG) {std::cout << "nbRand: " << nbRand << std::endl;}
    nbRand = nbRand % (max-min+1);
    if (nbRand > (3*(max-min+1)/(2*(nbInter1 - i))) || nbRand < ((max-min+1)/(2*(nbInter1 - i)))) {
      nbRand2 = randomGen.pseudorand();
      nbRand2 = nbRand2 % seuil1;
    }
    else {
      nbRand2 = -1;
    }
    while(nbRand % widthRoadV != 0 || nbRand2 > seuil2){
      nbRand = randomGen.pseudorand();
      if (DEBUG) {std::cout << "nbRand: " << nbRand << std::endl;}
      nbRand = nbRand % (max-min+1);
      if (nbRand > (3*(max-min+1)/(2*(nbInter1 - i))) || nbRand < ((max-min+1)/(2*(nbInter1 - i)))) {
	nbRand2 = randomGen.pseudorand();
	nbRand2 = nbRand2 % seuil1;
      }
      else {
	nbRand2 = -1;
      }
    }
    if (DEBUG) {std::cout << "Tour de boucle choix inter abs : " << i << std::endl;}
    absInter[i] = nbRand + min;
    min = absInter[i] + widthInter;
    max = max + widthInter;
    if (DEBUG) {std::cout << "nbRand : " << nbRand << std::endl;}
    if (DEBUG) {std::cout << "nbRand2 : " << nbRand2 << std::endl;}
    if (DEBUG) {std::cout << "absInter[i] : " << absInter[i] << std::endl;}
    if (DEBUG) {std::cout << "min : " << min << std::endl;}
    if (DEBUG) {std::cout << "max : " << max << std::endl;}
    assert(absInter[i] < MAP_WIDTH);
  }
  if (DEBUG) {std::cout << "generation1 : " << ++debugcpt << std::endl;};
  min = 0;
  max = MAP_HEIGHT - nbInter2*heightInter;
  if (DEBUG) {std::cout << "min : " << min << std::endl;}
  if (DEBUG) {std::cout << "max : " << max << std::endl;}
  for (j=0; j<nbInter2; j++) {
    nbRand = randomGen.pseudorand();
    if (DEBUG) {std::cout << "nbRand: " << nbRand << std::endl;}
    nbRand = nbRand % (max-min+1);
    if (nbRand > (3*(max-min+1)/(2*(nbInter2 - j))) || nbRand < ((max-min+1)/(2*(nbInter2 - j)))) {
      nbRand2 = randomGen.pseudorand();
      nbRand2 = nbRand2 % seuil1;
    }
    else {
      nbRand2 = -1;
    }
    while(nbRand % heightRoadH != 0 || nbRand2 > seuil2){
      nbRand = randomGen.pseudorand();
      nbRand = nbRand % (max-min+1);
      if (nbRand > (3*(max-min+1)/(2*(nbInter2 - j))) || nbRand < ((max-min+1)/(2*(nbInter2 - j)))) {
	nbRand2 = randomGen.pseudorand();
	nbRand2 = nbRand2 % seuil1;
      }
      else {
      nbRand2 = -1;
      }
    }
     if (DEBUG) {std::cout << "Tour de boucle choix inter ord : " << j << std::endl;}
    ordInter[j] = nbRand + min;
    min = ordInter[j] + heightInter;
    max = max + heightInter;
    if (DEBUG) {std::cout << "ordInter[j] : " << ordInter[j] << std::endl;}
    if (DEBUG) {std::cout << "min : " << min << std::endl;}
    if (DEBUG) {std::cout << "max : " << max << std::endl;}
    assert(ordInter[j] < MAP_HEIGHT);
  }

  if (DEBUG) {std::cout << "generation1 : " << ++debugcpt << std::endl;}; //9

  int abs0, ord0, abs1, ord1, longV, longH, k;
  abs0 = 0;
  ord0 = 0;
  for(i=0; i<nbInter1; i++){
    abs1 = absInter[i];
    // On parcoure les pâtés de maison "complets" sur une même route horizontale
    for(j=0; j<nbInter2; j++){
      ord1 = ordInter[j];
      // On met des batiments dans le pâté de maison
      nbRand = randomGen.pseudorand();
      fillBuildings(abs0, ord0, abs1 - 1, ord1 - 1, nbRand, nbLine, file);
      // On met la route verticale
      longV = (abs1 - abs0) / widthRoadV ;
      for(k=0; k<longV; k++) {
	for(i2=0; i2<widthRoadV; i2++){
	  for(j2=0; j2<heightInter; j2++){
	    //this->map[abs0 + k*widthRoadV + i2][ord1 + j2] = Tile(abs0 + k* widthRoadV + i2, ord1 + j2, ROADV, false, float(0.), float(1.), true, true, true, true, speedRoadV[i2][j2], Coordinates(abs0 + k* widthRoadV, ord1), Coordinates(0,0), NULL, fileRoadV, pictureRoadV, widthRoadV, heightInter);
	    this->map[abs0 + k*widthRoadV + i2][ord1 + j2] = Tile(abs0 + k* widthRoadV + i2, ord1 + j2, ROADV, false, float(0.), float(1.), j2<(heightInter - 1), j2>0, (abs0 + k*widthRoadV + i2) < (MAP_WIDTH - 1), (abs0 + k*widthRoadV + i2) > 0, 1., Coordinates(abs0 + k* widthRoadV, ord1), Coordinates(0,0), NULL, fileRoadV, pictureRoadV, widthRoadV, heightInter);
	  }
	}
      }
      // On met la route horizontale
      longH = (ord1 - ord0) / heightRoadH;
      for(k=0; k<longH; k++) {
	for(i2=0; i2<widthInter; i2++){
	  for(j2=0; j2<heightRoadH; j2++){
	    //this->map[abs1 + i2][ord0 + k*heightRoadH + j2] = Tile(abs1 + i2, ord0 + k*heightRoadH + j2, ROADH, false, float(0.), float(1.), true, true, true, true, speedRoadH[i2][j2], Coordinates(abs1, ord0 + k*heightRoadH), Coordinates(0,0), NULL, fileRoadH, pictureRoadH, widthInter, heightRoadH);
	    this->map[abs1 + i2][ord0 + k*heightRoadH + j2] = Tile(abs1 + i2, ord0 + k*heightRoadH + j2, ROADH, false, float(0.), float(1.),(ord0 + k*heightRoadH + j2) < (MAP_HEIGHT - 1), (ord0 + k*heightRoadH + j2)>0, i2 < (widthInter - 1), i2 > 0, 1., Coordinates(abs1, ord0 + k*heightRoadH), Coordinates(0,0), NULL, fileRoadH, pictureRoadH, widthInter, heightRoadH);
	  }
	}
      }
      // On met l'intersection
      for(i2=0; i2<widthInter; i2++){
	for(j2=0; j2<heightInter; j2++){
	  //this->map[abs1 + i2][ord1 + j2] = Tile(abs1 + i2, ord1 + j2, INTER, false, float(0.), float(1.), true, true, true, true, speedInter[i2][j2], Coordinates(abs1, ord1), Coordinates(0,0), NULL, fileInter, pictureInter, widthInter, heightInter);
	  this->map[abs1 + i2][ord1 + j2] = Tile(abs1 + i2, ord1 + j2, INTER, false, float(0.), float(1.), (ord1 + j2) < (MAP_HEIGHT - 1), (ord1 + j2) >  0, (abs1 + i2) < (MAP_WIDTH - 1), (abs1 + i2) >  0, 1., Coordinates(abs1, ord1), Coordinates(0,0), NULL, fileInter, pictureInter, widthInter, heightInter);
	}
      }
      ord0 = ord1 + heightInter;
    }
    // On s'occupe du bord droit de la carte, où il n'y a qu'un pâté de maison et une route horizontale
    ord1 = MAP_HEIGHT;
    nbRand = randomGen.pseudorand();
    fillBuildings(abs0, ord0, abs1 - 1, ord1 - 1, nbRand, nbLine, file);
    longH = (ord1 - ord0) / heightRoadH;
    for(k=0; k<longH; k++) {
      for(i2=0; i2<widthInter; i2++){
	for(j2=0; j2<heightRoadH; j2++){
	  //this->map[abs1 + i2][ord0 + k*heightRoadH + j2] = Tile(abs1 + i2, ord0 + k*heightRoadH + j2, ROADH, false, float(0.), float(1.), true, true, true, true, speedRoadH[i2][j2], Coordinates(abs1, ord0 + k*heightRoadH), Coordinates(0,0), NULL, fileRoadH, pictureRoadH, widthInter, heightRoadH);
	  this->map[abs1 + i2][ord0 + k*heightRoadH + j2] = Tile(abs1 + i2, ord0 + k*heightRoadH + j2, ROADH, false, float(0.), float(1.), (ord0 + k*heightRoadH + j2) < (MAP_HEIGHT - 1), (ord0 + k*heightRoadH + j2)>0, i2 < (widthInter - 1), i2 > 0, 1., Coordinates(abs1, ord0 + k*heightRoadH), Coordinates(0,0), NULL, fileRoadH, pictureRoadH, widthInter, heightRoadH);
	}
      }
    }
    abs0 = abs1 + widthInter;
    ord0 = 0;
  }
  // On s'occupe maintenant du bord bas de la carte, pour lequel il n'y a qu'un pâté de maison et une route verticale
  abs1 = MAP_WIDTH;
  // On parcoure les pates de maison "complets" sur une même route horizontale
  for(j=0; j<nbInter2; j++){
    ord1 = ordInter[j];
    // On met des batiments dans le paté de maison
    nbRand = randomGen.pseudorand();
    fillBuildings(abs0, ord0, abs1 - 1, ord1 - 1, nbRand, nbLine, file);
    // On met la route verticale
    longV = (abs1 - abs0) / widthRoadV ;
    for(k=0; k<longV; k++) {
      for(i2=0; i2<widthRoadV; i2++){
	for(j2=0; j2<heightInter; j2++){
	  //this->map[abs0 + k*widthRoadV + i2][ord1 + j2] = Tile(abs0 + k* widthRoadV + i2, ord1 + j2, ROADV, false, float(0.), float(1.), true, true, true, true, speedRoadV[i2][j2], Coordinates(abs0 + k* widthRoadV, ord1), Coordinates(0,0), NULL, fileRoadV, pictureRoadV, widthRoadV, heightInter);
	  this->map[abs0 + k*widthRoadV + i2][ord1 + j2] = Tile(abs0 + k* widthRoadV + i2, ord1 + j2, ROADV, false, float(0.), float(1.), j2<(heightInter-1), j2>0, (abs0 + k*widthRoadV + i2) < (MAP_WIDTH - 1), (abs0 + k*widthRoadV + i2) > 0, 1., Coordinates(abs0 + k* widthRoadV, ord1), Coordinates(0,0), NULL, fileRoadV, pictureRoadV, widthRoadV, heightInter);
	}
      }
    }
    ord0 = ord1 + heightInter;
  }
  ord1 = MAP_HEIGHT;
  nbRand = randomGen.pseudorand();
  fillBuildings(abs0, ord0, abs1 - 1, ord1 - 1, nbRand, nbLine, file);

  // We fill all the tiles still NULL (it's possible, cf. doc of the method)
  nbRand = randomGen.pseudorand();
  fillNull(nbRand, nbLine, file);
  
  if (DEBUG) {std::cout << "generation1 : " << ++debugcpt << std::endl;};
}

std::size_t Generation1::hachage(std::string seed) {
  boost::hash<std::string> string_hash;
  std::size_t seed1;
  seed1 = string_hash(seed);
  return(seed1);
}



void Generation1::fillBuildings(int abs0, int ord0, int abs1, int ord1, int seed, int nbLine, std::string file) {
  //J'ai choisis une valeur par défault pour la seed [Adrien K.]
  int nbRand = seed;
  PseudoRandom randomGen (seed);
  
  int fillbcpt = 0;
  
  if (DEBUG){std::cout << "fillBuildings : begin\n";}
  if (DEBUG){std::cout << "abs0: " << abs0 << std::endl;}
  if (DEBUG){std::cout << "ord0: " << ord0 << std::endl;}
  if (DEBUG){std::cout << "abs1: " << abs1 << std::endl;}
  if (DEBUG){std::cout << "ord1: " << ord1 << std::endl;}
  
  //if(abs0==abs1 || ord0==ord1){
  //if (DEBUG){std::cout << "fillBuildings : end" << std::endl;}
  //return;
  //}
  int i3, j3;
  int poidsBank = 13;
  int poidsHouse = 100;
  //srand(nbRand);
  int choose = -1;
  int poids = -1;
  Batiment batiment; 
  for(i3=0; i3<nbLine; i3++) {
    batiment = Batiment(file, i3);
    
    if (DEBUG){std::cout << "fillBuildings : " << fillbcpt++ << "\n";}
    if(batiment.getType()==BANK && batiment.getHeight() <= (ord1 - ord0 + 1) && batiment.getWidth() <= (abs1 - abs0 + 1)) {
      nbRand = randomGen.pseudorand();
      nbRand = nbRand % poidsBank;
      if (nbRand > poids) {choose = i3; poids = nbRand;}
    }
    
    if (DEBUG){std::cout << "fillBuildings : " << fillbcpt++ << "\n";}
    if(batiment.getType()==HOUSE && batiment.getHeight() <= (ord1 - ord0 + 1) && batiment.getWidth() <= (abs1 - abs0 + 1)) {
      nbRand = randomGen.pseudorand();
      nbRand = nbRand % poidsHouse;
      if (nbRand > poids) {choose = i3; poids = nbRand;}
    }
  }
  
  if (DEBUG){std::cout << "fillBuildings : " << fillbcpt++ << "\n";}
  if(choose==-1){
    if (DEBUG){std::cout << "fillBuildings : if " << choose << " " << abs1 << " " << ord1 <<"\n";}
    poids = -1;
    for(i3=0; i3<nbLine; i3++) {
      batiment = Batiment(file, i3);
      if (DEBUG){std::cout << "fillBuildings : " << fillbcpt++ << "\n";}
      if(batiment.getType()==BLANK) {
	nbRand = randomGen.pseudorand();
	if (nbRand > poids) {choose = i3; poids = nbRand;}
      }
    }
    if (DEBUG) {std::cout << "choix BLANK, ligne du bat : " << choose << std::endl;}
    batiment = Batiment(file, choose);
    std::string filePicture = batiment.getFilePictures();
    Coordinates picture = batiment.getPicture();
    for(i3=abs0; i3<=abs1; i3++){
      for(j3=ord0; j3<=ord1; j3++){
	if(DEBUG) {std::cout << i3 << " " << j3 << std::endl;}
	this->map[i3][j3] = Tile(i3,j3,TileType::BLANK,false, 0., 0., false, false, false, false, 0., Coordinates(i3, j3), Coordinates(0,0), NULL, filePicture, picture, 1, 1); // MrKulu : Pose problème quand les tiles blank ne sont pas de taille 1. TODO
      }
    }
  }
  else {
    if (DEBUG){std::cout << "fillBuildings : else " << choose << "\n";}
    batiment = Batiment(file, choose);
    int width = batiment.getWidth();
    int height = batiment.getHeight();
    std::string filePicture = batiment.getFilePictures();
    Coordinates picture = batiment.getPicture();
    floatMatrix speedBat = batiment.getSpeed();
    if (DEBUG){std::cout << "abs0: " << abs0 << std::endl;}
    if (DEBUG){std::cout << "ord0: " << ord0 << std::endl;}
    if (DEBUG){std::cout << "width: " << width << std::endl;}
    if (DEBUG){std::cout << "height: " << height << std::endl;}
    for(i3=abs0; i3<abs0 + width ; i3++){
      for(j3=ord0; j3<ord0 + height; j3++){
	//this->map[i3][j3] = Tile(i3,j3,batiment.getType(),false, 0., 0., false, false, false, false, speedBat[i3][j3], Coordinates(abs0, ord0), Coordinates(0,0), NULL, filePicture, picture, width, height);
	this->map[i3][j3] = Tile(i3,j3,batiment.getType(),false, 0., 0., false, false, false, false, 0., Coordinates(abs0, ord0), Coordinates(0,0), NULL, filePicture, picture, width, height);
      }
    }
    
    // on a rempli une partie du rectangle, on applique alors une réccurence pour compléter ce qui reste. Cette partie restante est l'union disjointe de deux rectangles.
    fillBuildings(abs0 + width, ord0, abs1, ord1, nbRand, nbLine, file);
    fillBuildings(abs0, ord0 + height, abs0 + width - 1 , ord1, nbRand, nbLine, file);
  }
  if (DEBUG){std::cout << "fillBuildings : end";}
  return;
}


void Generation1::fillNull(int seed, int nbLine, std::string file){
  int i, j, l;
  // We visit all the tiles of the map and we check if they are NULL
  Batiment batiment;
  int choose, poids;
  int nbRand = seed;
  PseudoRandom randomGen (seed);
  for(i=0; i<MAP_WIDTH; i++){
    for(j=0; j<MAP_HEIGHT; j++){
      if(getTile(i,j) == 0){
	if(DEBUG){std::cout << "NULL " << i << " " << j << std::endl;}
	// if the tile is NULL, we fill it with a BLANK tile
	// Firstly, we choose the sprite
	// We have to create a pseudo-random generator
	choose = -1;
	poids = -1;
	for(l=0; l<nbLine; l++){
	  batiment = Batiment(file, l);
	  if(batiment.getType()==BLANK){
	    nbRand = randomGen.pseudorand();
	    if (nbRand > poids) {choose = l; poids = nbRand;}
	  }
	}
	// Now, we fill the tile
	batiment = Batiment(file,choose);
	map[i][j] = Tile(i,j,batiment.getType(), false, 0., 0., false, false, false, false, 0., Coordinates(i,j), Coordinates(i,j), NULL, batiment.getFilePictures(), batiment.getPicture(), batiment.getWidth(), batiment.getHeight());
	if(DEBUG) {std::cout << "fill NULL with type : " << batiment.getType() << std::endl;}
      }
    }
  }
  // Now, there is not any NULL tile into the map
}

