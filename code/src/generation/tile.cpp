#include "tile.h"


enum TileType {roadH, roadV, intersection, banque, immeuble}; // énumération des types de batiments

Tile::Tile(int abs, int ord, TileType typeO, bool destructibleO, float anxietyO, float populationDensityO, bool gohO, bool gouO, bool gorO, bool golO, float speedO, Coordinates batOriginO, Coordinates boroughOrigin) {
  this->coord = new Coordinates(abs, ord);
  this->type = typeO;
  this->destructible = destructibleO;
  this->anxiety = anxietyO;
  this->populationDensity = populationDensityO;
  this->goh = gohO;
  this->gou = gouO;
  this->gol = golO;
  this->gor = gorO;
  this->speed = speedO;
  this->batOrigin = batOriginO;
  this->lenghtBat = getTLenght(typeO);
  this->weightBat = getTWeight(typeO);
  this->sprite = getTSprite(typeO); //à modifier, car cela dépend si origine ou pas
  this->destructionLevel = 0.;
  this->coordBorough = boroughOrigin;
}

float Tile::getAnxiety(){
  return this->anxiety;

}

void Tile::setAnxiety(float f){
  this->anxiety=f;
  return;
}

float Tile::getTLenght(TileType type) {
  switch (type) {
  case roadH: return 0;
  case roadV: return 0;
  case intersection: return 0;
  case banque: return 0;
  case immeuble: return 0;
  }
}

float Tile::getTWeight(TileType type) {
  switch (type) {
  case roadH: return 0;
  case roadV: return 0;
  case intersection: return 0;
  case banque: return 0;
  case immeuble: return 0;
  }
}

Sprite& Tile::getTSprite(TileType type) {
  switch (type) {
  case roadH: break;
  case roadV: break;
  case intersection: break;
  case banque: break;
  case immeuble: break;
  }
}
