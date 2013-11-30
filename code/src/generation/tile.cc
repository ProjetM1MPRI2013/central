#include "tile.h"

Coordinates::Coordinates(int abs, int ord) : abs(abs), ord(ord) {}

int Coordinates::getAbs() {
  return abs;
}

int Coordinates::getOrd() {
  return ord;
}


Tile::Tile(int abs, int ord, TileType typeO, bool destructibleO, float anxietyO, float populationDensityO, bool gohO, bool gouO, bool gorO, bool golO, float speedO, Coordinates& batOriginO, Coordinates& boroughOrigin) :
  coord(abs,ord),
  batOrigin(batOriginO),
  coordBorough(boroughOrigin) {
  this->type = typeO;
  this->destructible = destructibleO;
  this->anxiety = anxietyO;
  this->populationDensity = populationDensityO;
  this->goh = gohO;
  this->gou = gouO;
  this->gol = golO;
  this->gor = gorO;
  this->speed = speedO;
  //this->batOrigin = batOriginO;
  this->lenghtBat = getTLenght(typeO);
  this->weightBat = getTWeight(typeO);
  this->sprite = getTSprite(typeO); //à modifier, car cela dépend si origine ou pas
  this->destructionLevel = 0.;
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

sf::Sprite& Tile::getTSprite(TileType type) {
  switch (type) {
  case roadH: break;
  case roadV: break;
  case intersection: break;
  case banque: break;
  case immeuble: break;
  }
}

std::list<NPC*> Tile::getNPCs() {
  listNPC.sort([](NPC* a, NPC* b) { 
    Position ap = a->getPosition();
    Position bp = b->getPosition();
    return ap.getX() - ap.getY() < bp.getX() - bp.getY();
    });
};


void Tile::addNPC (NPC* a){
  listNPC.push_back(a);
  return;
};

void Tile::removeNPC (NPC* a){
  listNPC.remove(a);
  return;
};

Coordinates& Tile::getCoord() {
  return coord;
}
