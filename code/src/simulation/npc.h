#include "trajectory.h"

class NPC : public Positionable {
 private:
  Trajectory trajectory;
  float fear;
  bool shocked;
  float speed;
  
 public:
  NPC(float s,float f);
  float getFear();
  void setFear(float f);
  bool isShocked();
  void setShocked(bool s);
  void updateTrajectory(Trajectory t);
  float getSpeed();
  void setSpeed(float s);
  Position getPosition();
  void updatePosition(sf::Time dt,Geography const& map);
};
