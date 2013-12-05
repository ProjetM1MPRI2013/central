#include "player.h"

Player::Player (int pid, float xx, float yy) : p(xx,yy) {
  this->d = Direction::STOP;
  this->playerID = pid;
  this->speed = 1.;
};

int Player::getID(){
  return this->playerID;
};

Position* Player::getPosition() {
  return &(this->p);
};

Direction Player::getDirection () {
  return this->d;
};

std::list<Stuff*> Player::getInventory () {
  return this->inventory;
};

void Player::setDirection(Direction newd) {
  this->d = newd;
  return;
};

void Player::addItem(Stuff* s) {
  this->inventory.push_back(s);
  return;
};

void Player::removeItem(Stuff* s) {
  this->inventory.remove(s);
  return;
};

void Player::updatePosition(sf::Time dt) {
  float dep = (this->speed) * (dt.asSeconds());
  switch (this->d){
  case UP : 
    this->p.add(0,dep);
    break;
  case UPRIGHT :
    this->p.add(dep / 2, dep / 2);
    break;
  case RIGHT:
    this->p.add(dep,0);
    break;
  case RIGHTDOWN :
    this->p.add(dep/2,-dep/2);
    break;
  case DOWN :
    this->p.add(0,-dep);
    break;
  case DOWNLEFT :
    this->p.add(-dep/2,-dep/2);
    break;
  case LEFT :
    this->p.add(-dep,0);
    break;
  case LEFTUP :
    this->p.add(-dep/2,dep/2);
    break;
  case STOP :
    break;
  default:
    //ne doit pas arriver
    std::cerr << "Player::updatePosition : Direction not correct " << (int) (this->d) << "\n";
    break;
  };
  
  return;
};
