#include "batiment.h"
//j'ai bougé les includes dans le .h



Batiment::Batiment(std::string file, int line){
  std::fstream fichier;
  fichier.open(file, std::fstream::in);
  assert(fichier);
  std::string ligne, mot;
  int i = 1, j = 1;
  for(i = 0; i<=line; i++) {
    assert(getline(fichier, ligne));
  }
  fichier.close();
  std::size_t espace0 = 0; 
  std::size_t espace = ligne.find(" ");
  assert(espace!=std::string::npos);
  mot = ligne.substr (espace0, espace);

  this->type = TileType::BLANK; // default
  if (mot == "BANK")  { this->type = TileType::BANK;  }
  if (mot == "ROADH") { this->type = TileType::ROADH; }
  if (mot == "ROADV") { this->type = TileType::ROADV; }
  if (mot == "INTER") { this->type = TileType::INTER; }
  if (mot == "HOUSE") { this->type = TileType::HOUSE; }

  espace0 = espace + 1;
  espace = ligne.find(" ",espace0);
  assert(espace!=std::string::npos);
  mot = ligne.substr (espace0, espace - espace0 +1);
  this->height = atoi(mot.c_str());
  espace0 = espace + 1;
  espace = ligne.find(" ",espace0);
  assert(espace!=std::string::npos);
  mot = ligne.substr (espace0, espace - espace0 +1);
  this->width = atoi(mot.c_str());
  espace0 = espace + 1;
  espace = ligne.find(" ",espace0);
  assert(espace!=std::string::npos);
  mot = ligne.substr (espace0, espace - espace0 +1);
  std::string nombre;
  size_t espace1, espace2;
  espace2 = 2;
  for(i = 0; i<this->width; i++){
    for(j = 0; j<this->height; j++) {
      espace1 = espace2 + 1;
      espace2 = mot.find_first_of("|]",espace1);
      assert(espace2!=std::string::npos);
      nombre = mot.substr (espace1, espace2 - espace1 + 1);
      this->speed[i][j] = atof(nombre.c_str());
    }
    espace2 = mot.find_first_of("|]",espace1);
    assert(espace2!=std::string::npos);
  }
  espace0 = espace + 1;
  espace = ligne.find(" ",espace0);
  assert(espace!=std::string::npos);
  mot = ligne.substr (espace0, espace - espace0 +1);
  this->filePictures = mot;
  espace0 = espace + 1;
  espace = ligne.find(" ",espace0);
  assert(espace!=std::string::npos);
  mot = ligne.substr (espace0, espace - espace0 +1);
  espace1 = mot.find(",",1);
  assert(espace1!=std::string::npos);
  nombre = mot.substr (1, espace1-1);
  std::string nombre2;
  espace2 = mot.find(")",espace1+1);
  assert(espace2!=std::string::npos);
  nombre2 = mot.substr (espace1+1, espace2-espace1-1);


  //TODO
  //A priori cela ne va pas du tout, parce que picture ne sera jamais supprimé [Adrien K.]
  // j 'ai transformé nombre1 en nombre, j'espere que c'etait ce qui etait voulue
  this->picture = new Coordinates(atoi(nombre.c_str()), atoi(nombre2.c_str()));
}


Batiment::Batiment() {
  this->type = TileType::BLANK;
  this->height = 1;
  this->width = 1;
  this->speed[1][1] = 0;
  this->filePictures = "";
  this->picture = new Coordinates(0,0);
}


TileType Batiment::getType() {
  return(this->type);
}

int Batiment::getHeight() {
  return(this->height);
}

int Batiment::getWidth() {
  return(this->width);
}

floatMatrix Batiment::getSpeed() {
  return(this->speed);
}

std::string Batiment::getFilePictures() {
  return(this->filePictures);
}

Coordinates* Batiment::getPicture() {
  return(this->picture);
}

