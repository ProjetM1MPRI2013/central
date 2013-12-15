#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <list>
#include "position.h"
#include <SFML/System.hpp>
#include "../generation/geography.h"
#include <vector>
#include <cmath>
//#include <queue>
#include<boost/heap/fibonacci_heap.hpp>
#include "tilewrapper.h"

class Tile;
class Coordinates;

typedef typename boost::heap::fibonacci_heap<TileWrapper*,boost::heap::compare<TileWrapperComparator>> PriorityQueue;

/**
 * @brief The Trajectory class
 * contains the trajectory of a NPC
 */
class Trajectory {
 private:
  bool hasArrived;
  std::list<Position> posList;
  void explore(TileWrapper* y,TileWrapper* z,PriorityQueue& open);
  void pathfinding(Geography& map);

 public:

  /**
   * @brief Trajectory
   * the default constructor, creates a trajectory with default start and target Positions
   */
  Trajectory();

  /**
   * @brief Trajectory
   * creates a new Trajectory with given start and target Positions as references, so that the Trajectory's positions will be the same objects
   * @param start : the start position as a reference
   * @param target : the target position as a reference
   * @param map : the map where the pathfinding will be done
   */
  Trajectory(Position start,Position target,Geography& map);

  /**
   * @brief Trajectory
   * creates a new Trajectory by copying an existing one
   * it is a copy so the new Trajectory's Positions will not be the same objects as the first one's
   * @param t : the Trajectory to copy
   */
  Trajectory(Trajectory& t);

  /**
   * @brief getPosList
   * @return the Trajectory's Position list as a reference
   */
  std::list<Position>& getPosList();

  /**
   * @brief getPosition
   * @return the Trajectory's current Position as a reference
   */
  Position& getPosition();

  /**
   * @brief setPosition
   * sets the Trajectory's current Position
   * it should NOT be used with update, since update already changes this position
   * the server should use update to make the NPC move
   * @param p : the new position as a reference so the Trajectory's position will be the same object
   */
  void setPosition(Position& p);

  /**
   * @brief getHasArrived
   * @return a boolean true iff the NPC whose Trajectory it is has arrived at his target
   */
  bool getHasArrived();

  /**
   * @brief update
   * updates the Trajectory ie tells it to continue for a short time
   * @param dt : the time for which the Trajectory must continue
   * @param map : the map on which the Trajectory is located 
   */
  void update(sf::Time dt,float speed,Geography& map);
} ;

#endif //TRAJECTORY_H
