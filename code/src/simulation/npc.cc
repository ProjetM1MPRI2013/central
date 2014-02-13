/**
 * @author: Joseph
 */
#include "npc.h"
//#include "localState.h"
//#include "simulation.h"

/*it's included in npc.h*/
//#include "trajectory.h"

#define DEBUG false

NPC::NPC(float s,float f,float h,Position& start,TexturePack* tex) {
  trajectory = Trajectory(start);
  target = Position();
  shocked = false;
  speed = s;
  fear = f;
  hitboxSize = h;
  anim = Animation(tex);
  return;
}

NPC::NPC(float s,float f,float h,TexturePack* tex,boost::uuids::uuid uuid) : Positionable(uuid) {
  trajectory = Trajectory();
  target = Position();
  shocked = false;
  speed = s;
  fear = f;
  hitboxSize = h;
  anim = Animation(tex);
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


void NPC::setShocked(bool s) {
  shocked = s;
  return;
}


float NPC::getSpeed() const {
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
  trajectory.update(dt,speed,map,*this);
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

bool NPC::hasArrived() {
  return trajectory.getHasArrived();
}

void NPC::setAnim(const AnimType t){
  this->anim.setAnim(t);
  return;
}

Trajectory& NPC::getTrajectory() {
  return trajectory;
}

void NPC::setTrajectory(Trajectory& t) {
  trajectory = t;
  return;
}

float NPC::potential(Position p) {
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

std::pair<float,float> NPC::gradPot(Position p) {
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

void NPC::nextFrame()
{
  std::pair<float,float> speedVect = trajectory.getSpeed();
  float sp = sqrt(pow(speedVect.first,2)+pow(speedVect.second,2));
  if(sp >= 0.01 && anim.getAnim() != RUN)
    anim.setAnim(RUN);
  else if(sp < 0.01 && anim.getAnim() == RUN)
    anim.setAnim(IDLE);
  else
    anim.nextFrame();

  return;
}

Position NPC::getTarget() const {
  return target;
}

void NPC::setTarget(Position t, Geography& map) {
  target = t;
  trajectory.setTarget(t,map);
  return;
}
