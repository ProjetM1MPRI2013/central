#include "positionable.h"
#include "position.h"

Positionable::Positionable() {
  position = Position();
  return;
}

Positionable::Positionable(float x,float y) {
  position = Position(x,y);
  return;
}

Positionable::Positionable(Position& p) {
  position = Position(p);
  return;
}

Position& Positionable::getPosition() {
  return position;
}

void Positionable::setPosition(Position& p) {
  position = p;
  return;
}

