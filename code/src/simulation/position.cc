#include "position.h"
#include "../generation/tile.h"

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

Position::Position(Position& p) {
  x = p.getX();
  y = p.getY();
  return;
}

Position::Position(Tile& t) {
  x = TILE_SIZE_X*(0.5+(float)t.getCoord().getAbs());
  x = TILE_SIZE_Y*(0.5+(float)t.getCoord().getOrd());
  return;
}

float Position::getX() {
  return x;
}

float Position::getY() {
  return y;
}

void Position::setX(float x) {
  this->x = x;
  return;
}

void Position::setY(float y) {
  this->y = y;
  return;
}

void Position::add(float a,float b) {
  x+=a;
  y+=b;
  return;
}

Tile& Position::isInTile(Geography& map) {
  int i,j;
  i=x/TILE_SIZE_X;
  j=y/TILE_SIZE_Y;
  return (map.getTileRef(i,j));
}

float Position::distance(Position& p) {
  float dx,dy,d;
  dx = x-p.getX();
  dy = y-p.getY();
  d = sqrt(pow(dx,2)+pow(dy,2));
  return d;
}
