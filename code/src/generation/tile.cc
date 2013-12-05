#include "tile.h"
#include "position.h"
#include "npc.h"
#include "../simulation/tilewrapper.h"

Coordinates::Coordinates(int abs, int ord) : abs(abs), ord(ord) {}

int Coordinates::getAbs() {
  return abs;
}

int Coordinates::getOrd() {
  return ord;
}

bool Coordinates::equals(Coordinates& c) {
  return (abs==c.getAbs() && ord==c.getOrd());
}


Tile::Tile(int abs, int ord, TileType typeO, bool destructibleO, float anxietyO, float populationDensityO, bool gohO, bool gouO, bool gorO, bool golO, float speedO, Coordinates& batOriginO, Coordinates& boroughOrigin, SpriteTilePack* stp) :
  batOrigin(batOriginO),
  coord(abs,ord),
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
  // this->sprite = getTSprite(typeO); //à modifier, car cela dépend si origine ou pas // MrKulu : Inutile si je rajoute le SpriteTilePack : 
  this->stp = stp;
  this->sprite.setTexture(stp->texture);
  this->sprite.setTextureRect(sf::IntRect(stp->X1,stp->Y1,stp->X2,stp->Y2));
  this->destructionLevel = 0.;
  wrapper = NULL;
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
  case ROADH: return 0;
  case ROADV: return 0;
  case INTER: return 0;
  case BANK: return 0;
  case HOUSE: return 0;
  case BLANK: return 0;
  default: std::cerr << "Error : Tile : default case should not happen in getTLength";
  };
  return 10; //should not happens
}

float Tile::getTWeight(TileType type) {
  switch (type) {
  case ROADH: return 0;
  case ROADV: return 0;
  case INTER: return 0;
  case BANK: return 0;
  case HOUSE: return 0;
  case BLANK: return 0;
  default: std::cerr << "Error : Tile : default case should not happen in getTWeight";
  };
  return 10; //should not happens
}
/*
sf::Sprite& Tile::getTSprite(TileType type) {
  switch (type) {
  case ROADH: break;
  case ROADV: break;
  case INTER: break;
  case BANK: break;
  case HOUSE: break;
  case BLANK: break;
  default: std::cerr << "Error : Tile : default case should not happen in getTSprite";
  };
  //TODO
}*/

TileType Tile::getType(){
return (this -> type);}

std::list<NPC*> Tile::getNPCs() {
  listNPC.sort([](NPC* a, NPC* b) { 
    Position ap = a->getPosition();
    Position bp = b->getPosition();
    return ap.getX() - ap.getY() < bp.getX() - bp.getY();
    });
  return listNPC;
};

float Tile::getPopulationDensity(){
	return this->populationDensity;
}

void Tile::setPopulationDensity(float density){
	this->populationDensity=density;
}

float Tile::getSpeed(){
	return this->speed;
}

void Tile::setSpeed(float speed){
	this->speed=speed;
}

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


sf::Sprite Tile::getSprite(){
  return sprite;
}

void Tile::setTexture(SpriteTilePack* stp){
  this->stp = stp;
  this->sprite.setTexture(stp->texture);
  this->sprite.setTextureRect(sf::IntRect(stp->X1,stp->Y1,stp->X2,stp->Y2));
  return;
}
    
int Tile::getOriginSpriteX(){
  return stp->originX;
}
    
int Tile::getOriginSpriteY(){
  return stp->originY;
}

bool Tile::equals(Tile& t) {
  return (coord.equals(t.getCoord()));
}


TileWrapper* Tile::getWrapper() {
  return wrapper;
}

void Tile::setWrapper(TileWrapper* t) {
  wrapper = t;
  return;
}

void Tile::resetWrapper() {
  if (wrapper) {
    delete wrapper;
    wrapper = NULL;
  }
  return;
}


bool Tile::getGou() {
  return gou;
}

bool Tile::getGoh() {
  return goh;
}
bool Tile::getGor() {
  return gor;
}
bool Tile::getGol() {
  return gol;

}
