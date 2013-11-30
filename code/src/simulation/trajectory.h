#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <list>
#include "position.h"
#include <SFML/System.hpp>
#include "geography.h"
#include <vector>
#include <cmath>

class Tile;
class Coordinates;

class Trajectory {
 private:
  bool arrived;
  std::vector<std::reference_wrapper<Position>> posList;
 public:
  Trajectory();
  Trajectory(Position& start,Position& target);
  Trajectory(Trajectory& t);
  std::vector<std::reference_wrapper<Position>>& getPosList();
  Position& getPosition();
  bool getArrived();
  Tile& findNextTile(Tile& start,Tile& target);
  void update(sf::Time dt,float speed,Geography& map);
} ;

#endif //TRAJECTORY_H
