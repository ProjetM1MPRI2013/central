/**
 * @author: Joseph
 */
#include "positionable.h"
#include "position.h"

Positionable::Positionable() : FogDisabler() {
  position = Position();
  listen("Position::changedTile",position,&Positionable::changedTile);
  return;
}

Positionable::Positionable(boost::uuids::uuid uuid) : WithUuid(uuid), FogDisabler(), EventSource(), EventListener<Positionable>() {
  position = Position();
  listen("Position::changedTile",position,&Positionable::changedTile);
  return;
}

Positionable::Positionable(float x,float y) : FogDisabler() {
  position = Position(x,y);
  listen("Position::changedTile",position,&Positionable::changedTile);
  return;
}

Positionable::Positionable(Position& p) : FogDisabler() {
  position = Position(p);
  listen("Position::changedTile",position,&Positionable::changedTile);
  return;
}

Position& Positionable::getPosition() {
  return position;
}

void Positionable::setPosition(Position& p) {
  position.setX(p.getX());
  position.setY(p.getY());
  return;
}

void Positionable::changedTile(Position& p, std::pair<Coordinates,Coordinates> mod)
{
  trigger("Positionable::changedTile",mod);
  return;
}

