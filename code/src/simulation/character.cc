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
  //printf("NPC: sp1=%f, sp2=%f, speed=%f\n",speedVect.first,speedVect.second,speed);
  Position pDeltaT = getPosition();
  pDeltaT.add(deltaT * speedVect.first,deltaT*speedVect.second);
  float a, b, c;
  a = 0.5 * (p.distance(getPosition()) + p.distance(pDeltaT));
  c = 0.5 * speed * deltaT;
  if (a>c) {
    b = sqrt(pow(a,2)-pow(c,2));
  } else {
    b=0;
  }
  //  printf("NPC: a=%f,b=%f,c=%f\n",a,b,c);
  return Vzero*exp(-b/lambda);
}

std::pair<float,float> Character::gradPot(Position p) {
  //  float pot = potential(p);
  p.add(0.01,0);
  float potdx = potential(p);
  p.add(-0.02,0);
  float potmdx = potential(p);
  p.add(0.01,0.01);
  float potdy = potential(p);
  p.add(0,-0.02);
  float potmdy = potential(p);
  //  printf("NPC: potential %f %f %f %f\n",potdx,potmdx,potdy,potmdy);
  std::pair<float,float> grad ((potdx-potmdx)/0.02,(potdy-potmdy)/0.02);
  //printf("NPC: grad %f %f\n",grad.first,grad.second);
  return grad;
}

Position Character::getTarget() const {
  return target;
}
