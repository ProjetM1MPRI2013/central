#include "player.h"
#include "scenario/Stuff.h"
#include "scenario/StuffList.h"

#define SPEED_AMPLIFIER 350

#define DEBUG true
#include "debug.h"

void printDirection(Direction d){
  switch (d){
  case UP :
    std::cout << "UP";
    break;
  case  UPRIGHT :
    std::cout << "UPRIGHT";
   break;
  case  RIGHT :
    std::cout << "RIGHT";
   break;
  case  RIGHTDOWN :
    std::cout << "RIGHTDOWN";
   break;
  case  DOWN :
    std::cout << "DOWN";
   break;
  case  DOWNLEFT :
    std::cout << "DOWNLEFT";
   break;
  case  LEFT :
    std::cout << "LEFT";
   break;
  case  LEFTUP :
    std::cout << "LEFTUP";
   break;
  case  STOP :
    std::cout << "STOP";
   break;
  case ERROR :
 std::cout << "ERROR";
  default:
    std::cout << "printDirection : error";
  }
}


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
  if (isServer == 0){
    std::cout << "Client : player " << this->playerID << " changes direction from ";
  } else {
    std::cout << "Server : player " << this->playerID << " changes direction from ";
  }
  printDirection (this->d);
  std::cout << " to ";
  printDirection(newd);
  std::cout << "\n";
  this->d = newd;
  return;
};

void Player::addItem(Stuff* s) {
  this->inventory.push_back(s);
  DBG << "Add item to player " << this->playerID << " : " << s->name;
  return;
};

void Player::removeItem(Stuff* s) {
  this->inventory.remove(s);
  delete s;
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
