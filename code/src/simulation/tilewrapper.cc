#include "tilewrapper.h"
#include <cassert>
#include <cmath>


TileWrapper::TileWrapper() {
  tile = NULL;
  distance = -1;
  infinite = true;
  parent = NULL;
  heuristic = -1;
  open = false;
  closed = false;
  return;
}

TileWrapper::TileWrapper(Tile* t,Tile& s) {
  tile = t;
  t->setWrapper(this);
  distance = -1;
  infinite = true;
  parent = NULL;
  float i = s.getCoord().getAbs() - (*t).getCoord().getAbs();
  float j = s.getCoord().getOrd() - (*t).getCoord().getOrd();
  heuristic = sqrt(pow(i,2)+pow(j,2));
  open = false;
  closed = false;
  return;
}

float TileWrapper::getDistance() const {
  return distance;
}

void TileWrapper::setDistance(float d) {
  distance = d;
  return;
}

float TileWrapper::getHeuristic() const {
  return heuristic;
}

bool TileWrapper::isInfinite() const {
  return infinite;
}

void TileWrapper::setInfinite(bool b) {
  infinite = b;
  return;
}

bool TileWrapper::isOpen() const {
  return open;
}

void TileWrapper::setOpen(bool b) {
  open = b;
  return;
}

bool TileWrapper::isClosed() const {
  return closed;
}

void TileWrapper::setClosed(bool b) {
  closed = b;
  return;
}

TileWrapper* TileWrapper::getParent() {
  return parent;
}

void TileWrapper::setParent(TileWrapper* p) {
  parent = p;
  return;
}

bool TileWrapper::equals(TileWrapper& t) {
  return t.getTile().equals(*tile);
}

Tile& TileWrapper::getTile() {
  return *tile;
}



bool TileWrapperComparator::operator() (TileWrapper* lhs,TileWrapper* rhs) const {
  assert(!lhs->isInfinite() && !rhs->isInfinite());
  return ((lhs->getDistance()+lhs->getHeuristic()) > (rhs->getDistance()+lhs->getHeuristic()));
}
