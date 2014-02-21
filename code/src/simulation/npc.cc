/**
 * @author: Joseph
 */
#include "npc.h"
#include "boost/uuid/uuid_io.hpp"

#define DEBUG false

NPC::NPC(float s,float f,float h,Position& start,TexturePack* tex) : Character(s,start), DrawableObject(tex) {
  shocked = false;
  fear = f;
  hitboxSize = h;
  dying = false;
  dead = false;
  deathTimeout = sf::seconds(5);
  return;
}

NPC::NPC(float s,float f,float h,Position& start,
         TexturePack* tex,boost::uuids::uuid uuid) : 
  Character(s,start,uuid), DrawableObject(tex) {
  shocked = false;
  fear = f;
  hitboxSize = h;
  dying = false;
  dead = false;
  deathTimeout = sf::seconds(5);
  return;
}

float NPC::getFear() const {
  return fear;
}


void NPC::setFear(float f) {
  fear = f;
  return ;
}


bool NPC::isShocked() const {
  return shocked;
}

bool NPC::isDying() {
  return dying;
}

bool NPC::isDead() {
  return dead;
}

void NPC::setShocked(bool s) {
  shocked = s;
  return;
}


Position& NPC::getPosition() {
  return trajectory.getPosition();
}

void NPC::setPosition(Position& p) {
  trajectory.setPosition(p);
  Positionable::setPosition(p);
  return;
}

void NPC::updatePosition(sf::Time dt,Geography& map) {
  if (!dead && !dying) {
    trajectory.update(dt,speed,map,*this);
    Positionable::setPosition(trajectory.getPosition());
  }
  
  if (!dead && dying) {
    deathTimeout -= dt;
  }

  if (deathTimeout <= sf::Time::Zero) {
    dead = true;
  }

  if(DEBUG) {
    printf("NPC at %f %f\n",trajectory.getPosition().getX(),trajectory.getPosition().getY());
  }
  return;
}

float NPC::getHitboxSize() const {
  return hitboxSize;
}

bool NPC::isInHitbox(Position& p) {
  float d = p.distance(trajectory.getPosition());
  return (d<hitboxSize);
}


void NPC::setAnim(const AnimType t){
  this->anim.setAnim(t);
  return;
}


void NPC::nextFrame()
{
  std::pair<float,float> speedVect = trajectory.getSpeed();
  float sp = sqrt(pow(speedVect.first,2)+pow(speedVect.second,2));
  if(sp >= 0.01 && anim.getAnim() != RUN && anim.getAnim() != DEAD)
    anim.setAnim(RUN);
  else if(sp < 0.01 && anim.getAnim() == RUN)
    anim.setAnim(IDLE);
  else if(anim.getAnim() != DEAD && (dying || dead))
    anim.setAnim(DEAD);
  else
    anim.nextFrame();

  return;
}


void NPC::setTarget(Position t, Geography& map) {
  target = t;
  trajectory.setTarget(t,map);
  return;
}


void NPC::kill() {
  deathTimeout = sf::seconds(5);//il commence à mourir, il sera mort (et delete) dans 5 secondes
  dying = true;
  return;
}

std::ostream& operator<<(std::ostream& os, const NPC& npc) {
  os << "UUID: " << npc.getUuid() << "\n"
     << "speed: " << npc.getSpeed() << "\t"
     << "fear: " << npc.getFear() << "\t"
     << "hit size: " << npc.getHitboxSize() << "\n"
     << "position: " << npc.position << "\t"
     << "target: " << npc.getTarget();
  return os ;
}
