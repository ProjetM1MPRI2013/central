#include "positionable.h"
#include "position.h"

Positionable::Positionable() : FogDisabler() {
  position = Position();
  return;
}

Positionable::Positionable(float x,float y) : FogDisabler() {
  position = Position(x,y);
  return;
}

Positionable::Positionable(Position& p) : FogDisabler() {
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

