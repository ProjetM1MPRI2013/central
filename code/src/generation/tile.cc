#include "tile.h"
#include "../simulation/position.h"
#include "../simulation/npc.h"
#include "../simulation/tilewrapper.h"

#define DEBUG false

Coordinates::Coordinates(int abs, int ord) : abs(abs), ord(ord) {}

Coordinates::Coordinates(const Coordinates& a){
  this->abs = a.abs;
  this->ord = a.ord;
}

int Coordinates::getAbs() {
  return abs;
}

int Coordinates::getOrd() {
  return ord;
}

bool Coordinates::equals(Coordinates& c) {
  return (abs==c.getAbs() && ord==c.getOrd());
}



Tile::Tile(int abs, int ord, TileType typeO, bool destructibleO, float anxietyO, float populationDensityO, bool gohO, bool gouO, bool gorO, bool golO, float speedO, Coordinates batOriginO, Coordinates boroughOrigin, SpriteTilePack* stp0, std::string filePicturesO, Coordinates* pictureO, int widthO, int heightO) :
  batOrigin(batOriginO),
  coord(abs,ord),
  coordBorough(boroughOrigin),
  picture(pictureO){
  if (DEBUG){std::cout << "Tile : begin\n";}
  if (DEBUG){std::cout << abs << " " << ord << std::endl;}
  this->type = typeO;
  if (DEBUG){std::cout << typeO << std::endl;}
  this->destructible = destructibleO;
  this->anxiety = anxietyO;
  this->populationDensity = populationDensityO;
  this->goh = gohO;
  this->gou = gouO;
  this->gol = golO;
  this->gor = gorO;
  this->speed = speedO;
  //this->batOrigin = batOriginO;
  this->widthBat = widthO;
  this->heightBat = heightO;
  // this->sprite = getTSprite(typeO); //à modifier, car cela dépend si origine ou pas // MrKulu : Inutile si je rajoute le SpriteTilePack : 
  this->stp = stp0;
  if(this->stp)
    {
      this->sprite.setTexture(this->stp->texture);
      // this->sprite.setTextureRect(sf::IntRect(this->stp->X1,this->stp->Y1,this->stp->X2,this->stp->Y2));
    }  
  this->destructionLevel = 0.;
  wrapper = NULL;
  this->filePictures = filePicturesO;
  if (DEBUG){std::cout << "Tile : end\n";}
}

float Tile::getAnxiety(){
  return this->anxiety;

}

void Tile::setAnxiety(float f){
  this->anxiety=f;
  return;
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

std::list<NPC*>& Tile::getNPCs() {
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


sf::Sprite& Tile::getSprite(){
  sf::Sprite& rs = sprite;
  return rs;
}

void Tile::setTexture(SpriteTilePack* stp){
  this->stp = stp;
  if(stp != NULL)
    {
      this->sprite.setTexture(stp->texture);
      // this->sprite.setTextureRect(sf::IntRect(stp->X1,stp->Y1,stp->X2,stp->Y2));
    }
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
bool Tile::TextureIsInit() {
  return (this->stp != NULL);
}

std::string Tile::getFilePictures() {
  return(filePictures);
}

int Tile::getPictureX() {
  return(picture->getAbs());
}

int Tile::getPictureY() {
  return(picture->getOrd());
}

bool Tile::isBatOrigin() {
  return(coord.equals(batOrigin));
}

void Tile::printTileType(){
  //if (DEBUG) {std::cout << "Print Tile Type" << std::endl;}
  //std::cout << this->lenghtBat;
  //std::cout << this->type;
  switch(this->type){
  case ROADH:
    std::cout << "ROADH";
    break;
  case  ROADV:
    std::cout << "ROADV";
    break;
  case  INTER:
    std::cout << "INTER";
    break;
  case  BANK:
    std::cout << "BANK ";
    break;
  case  HOUSE:
    std::cout << "HOUSE";
    break;
  case  BLANK:
    std::cout << "BLANK";
    break;
  default:
    std::cerr << "Tile : printTileType error" << std::endl;
    break;
  }
  return;
};
