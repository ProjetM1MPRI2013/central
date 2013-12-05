#include "npc.h"
#include "localState.h"
#include "simulation.h"
#include "trajectory.h"

NPC::NPC(float s,float f,float h,Position& start,Position& target, Geography& map,TexturePack* tex) {
  trajectory = Trajectory(start,target,map);
  shocked = false;
  speed = s;
  fear = f;
  hitboxSize = h;
  anim = Animation(tex);
  return;
}

NPC::NPC(float s,float f,float h,TexturePack* tex) {
  trajectory = Trajectory();
  shocked = false;
  speed = s;
  fear = f;
  hitboxSize = h;
  anim = Animation(tex);
  return;
}


NPC::NPC(NPC& n) {
  trajectory = Trajectory(n.getTrajectory());
  shocked = n.isShocked();
  speed = n.getSpeed();
  fear = n.getFear();
  hitboxSize = n.getHitboxSize();
  anim = n.getAnim();
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

float NPC::getHitboxSize() {
  return hitboxSize;
}

bool NPC::isInHitbox(Position& p) {
  float d = p.distance(trajectory.getPosition());
  return (d<hitboxSize);
}

bool NPC::hasArrived() {
  return trajectory.getHasArrived();
}

sf::Sprite NPC::getSprite(){
  assert(this->anim.isInit());
  this->anim.nextFrame();                  // Pas certain 
  return this->anim.getSprite();
}

Animation NPC::getAnim(){
  return anim;
}

void NPC::setAnim(const int t){
  this->anim.setAnim(t);
  return;
}

void NPC::TextureAnim(TexturePack* tex){
  anim = Animation(tex);
  return;
}

Trajectory& NPC::getTrajectory() {
  return trajectory;
}

void NPC::setTrajectory(Trajectory& t) {
  trajectory = t;
  return;
}

int NPC::TextureOffsetX(){
  return anim.getOffsetX();
}

int NPC::TextureOffsetY(){
  return anim.getOffsetY();
}

bool NPC::TextureIsInit(){
  return anim.isInit();
}
