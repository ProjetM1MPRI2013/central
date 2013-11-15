#include "position.h"

Position(float x,float y) {
  this.x = x;
  this.y = y;
}

float Position::getX() {
  return x;
}

float Position::getY() {
  return y;
}

void Position::setX(float x) {
  this.x = x;
  return;
}

void Position::setY(float y) {
  this.y = y;
  return;
}

void Position::add(float a,float b) {
  x+=a;
  y+=b;
  return;
}
