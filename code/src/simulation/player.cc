#include "player.h"
#include "scenario/Stuff.h"
#include "scenario/StuffList.h"

#define SPEED_AMPLIFIER 350

Player::Player (int pid, float xx, float yy) : p(xx,yy) {
  this->d = Direction::STOP;
  this->playerID = pid;
  this->speed = 1.;
  this->addItem((Stuff *) (new Knife()));
  this->addItem((Stuff *) (new Bomb(2)));
  this->addItem((Stuff *) (new Gun(5,2,4)));
  this->addItem((Stuff *) (new Ammunition(10)));
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
  std::cout << "Client : player " << this->playerID << "changes direction \n";
  return;
};

void Player::addItem(Stuff* s) {
  this->inventory.push_back(s);
  std::cout << "Add item to player " << this->playerID << " : " << s->name << "\n";
  return;
};

void Player::removeItem(Stuff* s) {
  this->inventory.remove(s);
  return;
};

void Player::updatePosition(sf::Time dt) {
  float dep = (this->speed) * (dt.asSeconds()) * SPEED_AMPLIFIER;
  float sqrttwo = 1.414213562;
  switch (this->d){
  case UP : 
    this->p.add(0,-dep);
    break;
  case UPRIGHT :
    this->p.add(dep / sqrttwo, -dep / sqrttwo);
    break;
  case RIGHT:
    this->p.add(dep,0);
    break;
  case RIGHTDOWN :
    this->p.add(dep/sqrttwo,dep/sqrttwo);
    break;
  case DOWN :
    this->p.add(0,dep);
    break;
  case DOWNLEFT :
    this->p.add(-dep/sqrttwo,dep/sqrttwo);
    break;
  case LEFT :
    this->p.add(-dep,0);
    break;
  case LEFTUP :
    this->p.add(-dep/sqrttwo,-dep/sqrttwo);
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
