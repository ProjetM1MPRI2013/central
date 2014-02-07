/**
 * @author: Joseph
 */
#ifndef POSITION_H
#define POSITION_H

#include <utility>

#include "geography.h"


class Tile;
class Coordinates;
class Geography;
class NPC;

/**
 * @brief The Position class
 * it is a couple of floats with some useful methods
 */
class Position {
 private:
  int TILE_SIZE_X = 1;
  int TILE_SIZE_Y = 1;
  float x;
  float y;


 public:
  /**
   * @brief Position
   * the default constructor, it creates a new position with x=y=0
   */
  Position();

  /**
   * @brief Position
   * creates a new Position with coordinates (x,y)
   * @param x : the x coordinate
   * @param y : the y coordinate
   */
  Position(float x,float y);

  /**
   * @brief Position
   * creates a new position at the center of a given Tile
   * @param t : the given tile
   */
  Position(Tile& t);

  /**
   * @brief getX
   * @return the Position's x coordinate
   */
  float getX();

  /**
   * @brief setX
   * sets the Position's x coordinate
   * @param x : the new x coordinate
   */
  void setX(float x);

  /**
   * @brief getY
   * @return the Position's y coordinate
   */
  float getY();

  /**
   * @brief setY
   * sets the Position's y coordinate
   * @param y : the new y coordinate
   */
  void setY(float y);

  /**
   * @brief add
   * adds a float to each coordinate of the Position
   * @param a : the value to add to the x coordinate
   * @param b : the valud to add to the y coordinate
   */
  void add(float a,float b);

  /**
   * @brief isInTile
   * returns the Tile in which the Position is located on a map
   * @param map : the map
   * @return the Tile in which the Position is located
   */
  Tile& isInTile(Geography& map);

  /**
   * @brief isInTile : gives the indices corresponding to the tile this
   * position is in.
   * @return (i,j) if this position is in tile of absciss i and ordinate j.
   * Based on Tile& isInTile(Geography&).
   * If the call to this function return (i,j), then isInTile(map) returns map.getTile(i,j).
   */
  std::pair<int,int> isInTile() ;

  /**
   * @brief distance
   * computes the euclidean distance from the Position to another Position
   * @param p : the other Position
   * @return the distance between the two position
   */
  float distance(Position& p);

  /**
   * @brief getNPCList
   * computes the list of the NPCs whose hitbox contains the position
   */
  std::list<NPC*> getNPCList(Geography& map);

};
#endif
