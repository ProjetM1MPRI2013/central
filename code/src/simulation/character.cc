/**
 * @author: Joseph
 */
#include "character.h"


Character::Character(float s,Position& start) {
  trajectory = Trajectory(start);
  position = start;
  target = Position();
  Positionable::setPosition(trajectory.getPosition());
  speed = s;
  return;
}


Character::Character(float s,Position& start,boost::uuids::uuid uuid) : Positionable(uuid) {  
  trajectory = Trajectory(start);
  position = start;
  target = Position();
  Positionable::setPosition(trajectory.getPosition());
  speed = s;
  return;
}


float Character::getSpeed() const {
  return speed;
}


void Character::setSpeed(float s) {
  speed = s;
  return;
}


Trajectory& Character::getTrajectory() {
  return trajectory;
}


void Character::setTrajectory(Trajectory& t) {
  trajectory = t;
  Positionable::setPosition(t.getPosition());
  return;
}


bool Character::hasArrived() {
  return trajectory.getHasArrived();
}


float Character::potential(Position p) {
  std::pair<float,float> speedVect = trajectory.getSpeed();
  float speed = sqrt(pow(speedVect.first,2)+pow(speedVect.second,2));
  Position pDeltaT = getPosition();//position à t+deltaT 
  pDeltaT.add(deltaT * speedVect.first,deltaT*speedVect.second);
  /* a, b et c pour l'ellipse de foyers position et pDeltaT
     et où p se trouve*/
  float a, b, c;
  a = 0.5 * (p.distance(getPosition()) + p.distance(pDeltaT));
  c = 0.5 * speed * deltaT;
  if (a>c) {
    b = sqrt(pow(a,2)-pow(c,2));
  } else {
    b=0;
  }
  return Vzero*exp(-b/lambda);
}


std::pair<float,float> Character::gradPot(Position p) {
  p.add(0.01,0);
  float potdx = potential(p);
  p.add(-0.02,0);
  float potmdx = potential(p);
  p.add(0.01,0.01);
  float potdy = potential(p);
  p.add(0,-0.02);
  float potmdy = potential(p);
  std::pair<float,float> grad ((potdx-potmdx)/0.02,(potdy-potmdy)/0.02);
  return grad;
}


Position Character::getTarget() const {
  return target;
}
