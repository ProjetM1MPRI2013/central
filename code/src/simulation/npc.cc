#include "npc.h"
#include "localState.h"
#include "simulation.h"
#include "trajectory.h"

NPC::NPC(float s,float f,float h,Position& start,Position& target, sf::Texture& tex) {
  trajectory = Trajectory(start,target);
  shocked = false;
  speed = s;
  fear = f;
  hitboxSize = h;
  this->anim = Animation(tex,{1,12,16},{16,16,32},32,{0,0,0},{0,0,0},{false,true,false}); // Pour tester
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

Position& NPC::getPosition() {
  return (this->trajectory).getPosition();
}

void NPC::setPosition(Position& p) {
  trajectory.setPosition(p);
  return;
}

void NPC::updatePosition(sf::Time dt,Geography& map) {
  trajectory.update(dt,speed,map);
  return;
}

bool NPC::isInHitbox(Position& p) {
  float d = p.distance(trajectory.getPosition());
  return (d<hitboxSize);
}

bool NPC::hasArrived() {
  return trajectory.getHasArrived();
}

sf::Sprite NPC::getSprite(){
  this->anim.nextFrame()                  // Pas certain 
  return this->anim.getSprite();
}

void NPC::setAnim(AnimType t){
  this->anim.setAnim(t);
  return;
}

