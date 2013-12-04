#include "batiment.h"
#include <fstream>
#include <assert.h> 

Batiment::Batiment(string file, int line){
  ifstream fichier(file, ios::in);
  assert(fichier);
  string ligne, mot;
  for(i=1; i<=line; i++) {
    assert(getline(fichier, ligne));
  }
  fichier.close();
  size_t espace0 = 0; 
  size_t espace = ligne.find(" ");
  assert(espace!=string::npos);
  mot = ligne.substr (espace0, espace);
  switch (mot) {
  case "BANK": {
    this->type = BANK;
      }
  case "ROADH": {
    this->type = ROADH;
  }
  case "ROADV": {
    this->type = ROADV;
  }
  case "INTER": {
    this->type = INTER;
  }
  case "HOUSE": {
    this->type = HOUSE;
  }
  case "BLANK": {
    this->type = BLANK;
  }
  }
  espace0 = espace + 1;
  espace = ligne.find(" ",espace0);
  assert(espace!=string::npos);
  mot = ligne.substr (espace0, espace - espace0 +1);
  this->weight = atoi(mot.c_str());
  espace0 = espace + 1;
  espace = ligne.find(" ",espace0);
  assert(espace!=string::npos);
  mot = ligne.substr (espace0, espace - espace0 +1);
  this->lenght = atoi(mot.c_str());
  espace0 = espace + 1;
  espace = ligne.find(" ",espace0);
  assert(espace!=string::npos);
  mot = ligne.substr (espace0, espace - espace0 +1);
  string nombre;
  size_t espace1, espace2;
  espace2 = 2;
  for(i=0; i<this.lenght; i++){
    for(j=0; j<this.weight; j++) {
      espace1 = espace2 + 1;
      espace2 = mot.find_first_of("|]",espace1);
      assert(espace2!=string::npos);
      nombre = mot.substr (espace1, espace2 - espace1 + 1);
      this->speed[i][j] = atof(nombre.c_str());
    }
    space2 = mot.find_first_of("|]",espace1);
    assert(espace2!=string::npos);
  }
  espace0 = espace + 1;
  espace = ligne.find(" ",espace0);
  assert(espace!=string::npos);
  mot = ligne.substr (espace0, espace - espace0 +1);
  this->filePicture = mot;
  espace0 = espace + 1;
  espace = ligne.find(" ",espace0);
  assert(espace!=string::npos);
  mot = ligne.substr (espace0, espace - espace0 +1);
  espace1 = mot.find(",",1);
  assert(espace1!=string::npos);
  nombre = mot.substr (1, espace1-1);
  string nombre2;
  espace2 = mot.find(")",espace1+1);
  assert(espace2!=string::npos);
  nombre2 = mot.substr (espace1+1, espace2-espace1-1);
  this->picture = new Coordinates(atoi(nombre1.c_str()), atoi(nombre2.c_str()));
}


TileType Batiment::getType() {
  return(this.type);
}

int Batiment::getWeight() {
  return(this.weight);
}

int Batiment::getLenght() {
  return(this.lenght);
}

float[][] Batiment::getSpeed() {
  return(this.speed);
}

string Batiment::getFilePictures() {
  return(this.filePictures);
}

Coordinates Batiment::getPicture() {
  return(this.picture);
}

