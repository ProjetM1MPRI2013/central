#include "localState.h"
#include "simulation.h"

NPC(float s,float f) {
  shocked = false;
  speed = s;
  fear = f;
  return;
}

float NPC::getFear() {
  return fear;
}


void NPC::setFear(float f) {
  fear = f;
  return ;
}


bool NPC::isShocked() {
  return shocked;
}


void NPC::setShocked(bool s) {
  shocked = s;
  return;
}


float NPC::getSpeed() {
  return speed;
}

void NPC::setSpeed(float s) {
  speed = s;
  return;
}

Position getPosition() {
  return trajectory.getPosition();
}

void updatePosition(sf::Time dt,Geography const& map) {
  trajectory.updatePosition(dt,speed,map);
}
