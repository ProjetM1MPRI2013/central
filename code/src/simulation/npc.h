#ifndef NPC_H
#define NPC_H
#include "trajectory.h"
#include "localState.h"
#include "positionable.h"
#include "position.h"
#include <SFML/System.hpp>

class NPC {
 private:
  Trajectory trajectory;
  float fear;
  bool shocked;
  float speed;
  float hitboxSize;

 public:
  NPC(float s,float f,float h,Position& start,Position& target);
  float getFear();
  void setFear(float f);
  bool isShocked();
  void setShocked(bool s);
  void updateTrajectory(Trajectory t);
  float getSpeed();
  void setSpeed(float s);
  Position& getPosition();
  void updatePosition(sf::Time dt,Geography& map);
  bool isInHitbox(Position& p);
};
#endif
