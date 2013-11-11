#include "position.h"

class Trajectory {
 private:
  vector<Position> posList;
 
 public:
  vector<Position> getPosList();
  void setPosList(Position p);
  Position getCurrentPos();
  void updateTrajectory(sf::Time dt,float speed,Geography const& map);
}
