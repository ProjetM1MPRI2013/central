#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "position.h"
#include <SFML/System.hpp>
#include "geography.h"

class Trajectory {
 private:
  vector<Position> posList;
 
 public:
  vector<Position> getPosList();
  void setPosList(Position p);
  Position getCurrentPos();
  void updateTrajectory(sf::Time dt,float speed,Geography const& map);
} ;

#endif //TRAJECTORY_H
