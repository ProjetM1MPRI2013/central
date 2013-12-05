#ifndef TILE_WRAPPER_H
#define TILE_WRAPPER_H

#include "../generation/tile.h"

class TileWrapper {
 private:
  Tile* tile;
  float distance;
  float heuristic;
  TileWrapper* parent;
  bool infinite;
  bool open;
  bool closed;

 public:
  TileWrapper();
  TileWrapper(Tile* t,Tile& s);
  float getDistance() const;
  void setDistance(float d);
  float getHeuristic() const;
  bool isInfinite() const;
  void setInfinite(bool b);
  bool isOpen() const;
  void setOpen(bool b);
  bool isClosed() const;
  void setClosed(bool b);
  TileWrapper* getParent();
  void setParent(TileWrapper* p);
  bool equals(TileWrapper& t);
  Tile& getTile();
};


class TileWrapperComparator {
 public:
  bool operator() (TileWrapper* lhs,TileWrapper* rhs) const;
};

#endif
