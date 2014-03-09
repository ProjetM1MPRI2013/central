/**
 * @author: Joseph
 */
#include "position.h"
#include "../generation/tile.h"
#include "npc.h"
#include <cmath>

Position::Position() {
  Position(0,0);
  return;
}


Position::Position(float x,float y) {
  this->x = x;
  this->y = y;
  return;
}


Position::Position(Tile& t) {
  x = TILE_SIZE_X*(0.5+t.getCoord().getAbs());
  y = TILE_SIZE_Y*(0.5+t.getCoord().getOrd());
  return;
}


float Position::getX() const {
  return x;
}


float Position::getY() const {
  return y;
}


void Position::setX(float x) {
  int xt = floor(this->x), xn = floor(x), yf = floor(y);
  this->x = x;
  if(xt != xn)
    trigger("Position::changedTile", std::pair<Coordinates,Coordinates>(Coordinates(xt,yf),Coordinates(xn,yf)));
  return;
}


void Position::setY(float y) {
  int yt = floor(this->y), yn = floor(y), xf = floor(x);
  this->y = y;
  if(yt != yn)
    trigger("Position::changedTile", std::pair<Coordinates,Coordinates>(Coordinates(xf, yt),Coordinates(xf,yn)));

  return;
}


void Position::add(float a,float b) {
  int x1 = floor(x), x2 = floor(x+a), y1 = floor(y), y2 = floor(y+b);
  x+=a;
  y+=b;
  if(x1 != x2 || y1 != y2)
    trigger("Position::changedTile", std::pair<Coordinates,Coordinates>(Coordinates(x1,y1),Coordinates(x2,y2)));
  return;
}


Tile& Position::isInTile(Geography& map) {
  int i,j;
  i=x/TILE_SIZE_X;
  j=y/TILE_SIZE_Y;
  return (map.getTileRef(i,j));
}


std::pair<int,int> Position::isInTile(){
  return std::pair<int,int>(x/TILE_SIZE_X, y/TILE_SIZE_Y) ;
}


float Position::distance(const Position &p) const {
  float dx,dy,d;
  dx = x-p.getX();
  dy = y-p.getY();
  d = sqrt(pow(dx,2)+pow(dy,2));
  return d;
}

bool Position::equal(const Position &p) const {
  return (p.x == x && p.y == y);
}


std::list<NPC*> Position::getNPCList(Geography& map) {
  std::list<NPC*> npcList;
  //get the list of all NPCs around this position
  std::list<NPC*> notTooFarNPCs = isInTile(map).getNPCsInRadius(map,3);
  while (!notTooFarNPCs.empty()) {
    // keep only those who are alive and whose hitbox contains the position
    NPC* npc = notTooFarNPCs.front();
    notTooFarNPCs.pop_front();
    if (npc->isInHitbox(*this) && !(npc->isDying())&& !(npc->isDead())) {
      npcList.push_front(npc);
    }
  }
  return npcList;
}


std::ostream& operator<<(std::ostream& os, const Position& obj) {
  os << "(" << obj.getX() << ", " << obj.getY() << ")" ;
  return os ;
}
