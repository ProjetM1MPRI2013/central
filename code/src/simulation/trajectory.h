#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <list>
#include "position.h"
#include <SFML/System.hpp>
#include "geography.h"

class Trajectory {
 private:
  std::vector<Position> posList;
 
 public:
  std::vector<Position> getPosList();
  void setPosList(Position p);
  Position getPosition();
  void update(sf::Time dt,float speed,Geography const& map);
} ;

#endif //TRAJECTORY_H
