#ifndef TILE_WRAPPER_H
#define TILE_WRAPPER_H

#include "../generation/tile.h"

/**
 * @brief The TileWrapper class
 * it is a wrapper that contains a pointer to a tile and some variables needed to do the pathfinding,
 * and which would be weird in Tile.
 * A Tile should have at most one TileWrapper, and only during the ppathfinding computation
 * The wrapper is then deleted.
 */
class TileWrapper {
 private:
  Tile* tile;
  float distance;
  float heuristic;
  TileWrapper* parent;
  bool open;
  bool closed;


 public:
  /**
   * @brief TileWrapper
   * the default constructor,
   * it creates a new empty TileWrapper
   */
  TileWrapper();

  /**
   * @brief TileWrapper
   * creates a new TileWrapper wrapping the tile t when target is the target tile
   * @param t: a pointer to the tile to wrap
   * @param s: the target tile (for the pathfinding)
   */
  TileWrapper(Tile* t,Tile& target);
  
  /**
   * @brief getDistance
   * @return the calculated distance from the start tile
   */
  float getDistance() const;

  /**
   * @brief setDistance
   * sets the calculated distance from the start Tile
   * @param d: the new distance
   */
  void setDistance(float d);

  /**
   * @brief getHeuristic
   * @return the heuristic for this tile, ie its (actual) distance to the target tile
   */
  float getHeuristic() const;

  /**
   * @brief isOpen
   * @return true iff the tilewrapper is in Open (during the pathfinding)
   */
  bool isOpen() const;

  /**
   * @brief setOpen
   * sets the value of the open boolean
   * @param b: the new open value
   */
  void setOpen(bool b);

  /**
   * @brief isClosed
   * @return true iff the tilewrapper is in Closed (during the pathfinding)
   */
  bool isClosed() const;

  /**
   * @brief setClosed
   * sets the value of the closed boolean
   * @param b: the new open value
   */
  void setClosed(bool b);

  /**
   * @brief getParent
   * @return a pointer to the Tile's parent (during the pathfinding)
   */
  TileWrapper* getParent();

  /**
   * @brief setParent
   * set the Tile's parent
   * @param p: a pointer to the new parent
   */
  void setParent(TileWrapper* p);

  /**
   * @brief equals
   * checks whether the TileWrapper is equal to another TileWrapper
   * ie if their Tiles are equal
   */
  bool equals(TileWrapper& t);

  /**
   * @brief getTile
   * @return the tile wrapped as a reference
   */
  Tile& getTile();
};


/**
 * @brief The TileWrapperComparator class
 * a comparator for pointers on TileWrapper
 * the greatest is the one with the lowest distance+heuristique
 * (asserts that they actually have a distance)
 */
class TileWrapperComparator {
 public:
  bool operator() (TileWrapper* lhs,TileWrapper* rhs) const;
};

#endif
