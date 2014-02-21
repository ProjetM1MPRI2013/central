/**
 * @author: Maxime, Joseph, Lucas
 */
#include "tile.h"
#include "../simulation/position.h"
#include "../simulation/npc.h"
#include "../simulation/tilewrapper.h"
#include "debug.h"
#include "../scenario/Stuff.h"
#include "../scenario/StuffList.h"

#define DEBUG false


Coordinates::Coordinates(int abs, int ord) : abs(abs), ord(ord) {}


Coordinates::Coordinates() {
  this->abs = 0;
  this->ord = 0;
}


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


void Coordinates::setAbs(int absO) {
  this->abs = absO;
  return;
}


void Coordinates::setOrd(int ordO) {
  this->ord = ordO;
  return;
}


Tile::Tile(int abs, int ord, TileType typeO, bool destructibleO, float anxietyO, float populationDensityO, bool gouO, bool godO, bool gorO, bool golO, float speedO, Coordinates batOriginO, Coordinates boroughOrigin, SpriteTilePack* stp0, std::string filePicturesO, Coordinates pictureO, int widthO, int heightO) :
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
  this->gou = gouO;
  this->god = godO;
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
  alpha = false;
  fog = 0;
  buildfog = false;

  if (DEBUG){std::cout << "Tile : end\n";}

  //Nobody :  on met des fleurs pour le test
  C_Flower* f = new C_Flower();
  this->listStuff.push_front(f);

  }


Tile::Tile() :
  batOrigin(Coordinates()),
  coord(0,0),
  coordBorough(Coordinates()),
  picture(Coordinates()) {
  wrapper = nullptr;
  alpha = false;
  fog = 0;
  buildfog = false;
}


Tile::Tile(const Tile& t) :
  batOrigin(t.batOrigin),
  coord(t.coord),
  coordBorough(t.coordBorough),
  picture(t.picture){
  type = t.type;
  destructible = t.destructible;
  anxiety = t.anxiety;
  populationDensity = t.populationDensity;
  gou = t.gou;
  god = t.god;
  gol = t.gol;
  gor = t.gor;
  speed = t.speed;
  widthBat = t.widthBat;
  heightBat = t.heightBat;

  stp = t.stp; 
  if (stp) { sprite.setTexture(stp->texture); }
  wrapper = t.wrapper;

  destructionLevel = t.destructionLevel;
  filePictures = t.filePictures;
  alpha = t.alpha;
  fog = t.fog;
  buildfog = false;
  this->listStuff = t.listStuff;
}


Tile& Tile::operator=(const Tile& t){
  if (this != &t){
    batOrigin = t.batOrigin;
    coord = t.coord;
    coordBorough = t.coordBorough;
    picture = t.picture;
    type = t.type;
    destructible = t.destructible;
    anxiety = t.anxiety;
    populationDensity = t.populationDensity;
    gou = t.gou;
    god = t.god;
    gol = t.gol;
    gor = t.gor;
    speed = t.speed;
    widthBat = t.widthBat;
    heightBat = t.heightBat;
    
    stp = t.stp; 
    if (stp) { sprite.setTexture(stp->texture); }
    wrapper = t.wrapper;

    destructionLevel = t.destructionLevel;
    filePictures = t.filePictures;
    alpha = t.alpha;
    fog = t.fog;
    buildfog = false;
    this->listStuff = t.listStuff;
  }
  return *this;
}


void Tile::nobodyTile(){
  DBG << "tile : " << this->getCoord().abs << "," << this->getCoord().ord;
}


float Tile::getAnxiety(){
  return this->anxiety;
}


void Tile::setAnxiety(float f){
  DBG << "nobody : anxiety : " << f << "in " ;
  nobodyTile();
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


void Tile::setType(TileType t){
  this->type = t;
  return;
}


std::list<NPC*>& Tile::getNPCs() {
  listNPC.sort([](NPC* a, NPC* b) { 
      Position ap = a->getPosition();
      Position bp = b->getPosition();
      return ap.getY() - ap.getX() < bp.getY() - bp.getX();
    });
  return listNPC;
}


std::list<Clickable*>& Tile::getStuffs() {
  return listStuff;
}


float Tile::getPopulationDensity(){
  return this->populationDensity;
}


void Tile::setPopulationDensity(float density){
  this->populationDensity=density;
}


bool Tile::isDestructible() {
  return (destructible) ;
}


float Tile::getSpeed(){
  return this->speed;
}


void Tile::setSpeed(float speed){
  this->speed=speed;
}


void Tile::addNPC (NPC* a){
  listNPC.push_front(a);
  return;
}


void Tile::removeNPC (NPC* a){
  listNPC.remove(a);
  return;
}


void Tile::addStuff (Clickable* a){
  listStuff.push_front(a);
  return;
}


void Tile::removeStuff (Clickable* a){
  listStuff.remove(a);
  return;
}


Coordinates& Tile::getCoord() {
  return coord;
}


void Tile::setCoord(Coordinates& coordO) {
  this->coord = coordO;
  return;
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


bool Tile::getGod() {
  return god;
}


bool Tile::getGou() {
  return gou;
}


bool Tile::getGor() {
  return gor;
}


bool Tile::getGol() {
  return gol;
}


void Tile::setGod(bool goD){
  this->god = goD;
  return;
}


void Tile::setGou(bool goU){
  this->gou = goU;
  return;
}


void Tile::setGor(bool goR){
  this->gor = goR;
  return;
}


void Tile::setGol(bool goL){
  this->gol = goL;
  return;
}


Coordinates& Tile::getBatOrigin() {
  return (this->batOrigin);
}


void Tile::setBatOrigin(Coordinates& p) {
  this->batOrigin = p;
  return;
}


Coordinates& Tile::getCoordBorough() {
  return (this->coordBorough);
}


void Tile::setCoordBorough(Coordinates& p) {
  this->coordBorough = p;
  return;
}


int Tile::getWidthBat() {
  return widthBat;
}


void Tile::setWidthBat(int w) {
  this->widthBat = w;
  return;
}


int Tile::getHeightBat() {
  return heightBat;
}


void Tile::setHeightBat(int h) {
  this->heightBat = h;
  return;
}


bool Tile::TextureIsInit() {
  return (this->stp != NULL);
}


std::string Tile::getFilePictures() {
  return(filePictures);
}


int Tile::getPictureX() {
  return(picture.getAbs());
}


int Tile::getPictureY() {
  return(picture.getOrd());
}


bool Tile::isBatOrigin() {
  return((coord.getAbs() == batOrigin.getAbs() + widthBat - 1) && (coord.getOrd() == batOrigin.getOrd()));
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
}


std::list<Tile*> Tile::getNeighbourTiles(Geography& map) {
  std::list<Tile*> neighbourTiles;
  if (getGod()) {
    neighbourTiles.push_front(map.getTile(coord.getAbs(),coord.getOrd()-1));
  }
  if (getGol()) {
    neighbourTiles.push_front(map.getTile(coord.getAbs()-1,coord.getOrd()));
  }
  if (getGor()) {
    neighbourTiles.push_front(map.getTile(coord.getAbs()+1,coord.getOrd()));
  }
  if (getGou()) {
    neighbourTiles.push_front(map.getTile(coord.getAbs(),coord.getOrd()+1));
  }
  return neighbourTiles;
}


std::list<Tile*> Tile::getTilesInRadius(Geography& map,int r) {
  std::list<Tile*> tilesInRadius;
  for (int i=std::max(coord.getAbs()-r,0);i<std::min(coord.getAbs()+r+1,map.getMapWidth());i++) {
    for (int j=std::max(coord.getOrd()-r,0);j<std::min(coord.getOrd()+r+1,map.getMapHeight());j++) {
      tilesInRadius.push_front(map.getTile(i,j));
    }
  }
  return tilesInRadius;
}
      
  
std::list<NPC*> Tile::getNPCsInRadius(Geography& map,int r) {
  std::list<NPC*> notTooFarNPCs;
  std::list<Tile*> neighbourTiles = getTilesInRadius(map,r);
  Tile* tempTile;
  while (!neighbourTiles.empty()) {
    tempTile = neighbourTiles.front();
    neighbourTiles.pop_front();
    std::list<NPC*> tempTileNPCs = tempTile->getNPCs();
    notTooFarNPCs.splice(notTooFarNPCs.end(),tempTileNPCs);
  }
  return notTooFarNPCs;
}


bool Tile::isAligned(Tile& tile1,Tile& tile2) {
  Coordinates coord1 = tile1.getCoord();
  Coordinates coord2 = tile2.getCoord();
  bool hor = (coord1.getOrd() == coord2.getOrd()) && (coord2.getOrd() == coord.getOrd());
  bool ver = (coord1.getAbs() == coord2.getAbs()) && (coord2.getAbs() == coord.getAbs());
  bool dir = false;
  bool inv = false;
  if (hor) {
    dir = (coord1.getAbs()+1 == coord2.getAbs()) && (coord2.getAbs()+1 == coord.getAbs());
    inv = (coord1.getAbs()-1 == coord2.getAbs()) && (coord2.getAbs()-1 == coord.getAbs());
  }
  if (ver) {
    dir = (coord1.getOrd()+1 == coord2.getOrd()) && (coord2.getOrd()+1 == coord.getOrd());
    inv = (coord1.getOrd()-1 == coord2.getOrd()) && (coord2.getOrd()-1 == coord.getOrd());
  }
  return (dir || inv);
}

    
bool Tile::isWalkable()
{
  return speed > 0.01;
}


bool Tile::isInFog()
{
  return fog == 0;
}


void Tile::setAlpha(bool a)
{
  if(alpha != a && !(isWalkable()))
    {
      if(a)
	sprite.setColor(sf::Color(255,255,255,128));
      else
	sprite.setColor(sf::Color(255,255,255));
    }
  alpha = a;
  return;
}


void Tile::setBuildFog(int nbFog)
{
  bool w = (2*nbFog > widthBat*heightBat);
  if((buildfog != w) && !(isWalkable()))
    {
      if(w)
	sprite.setColor(sf::Color(128,128,128));
      else
	sprite.setColor(sf::Color(255,255,255));
    }
  buildfog = w;
  return;
}


void Tile::setFog(int modfog){
  fog += modfog;
  fog = std::max(0,fog);
  return;
}
