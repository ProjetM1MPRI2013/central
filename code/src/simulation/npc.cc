#include "npc.h"
#include "localState.h"
#include "simulation.h"
//#include "trajectory.h"

NPC::NPC(float s,float f) : Positionable(0,0) {
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

Position NPC::getPosition() {
  return (this->trajectory).getPosition();
}

void NPC::updatePosition(sf::Time dt,Geography const& map) {
  trajectory.update(dt,speed,map);
}
