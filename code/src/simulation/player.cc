#include <algorithm>
#include "player.h"
#include "scenario/Stuff.h"
#include "scenario/StuffList.h"

#define SPEED_AMPLIFIER 8

#define DEBUG false
#include "debug.h"


StuffNotFound::StuffNotFound() :
  std::runtime_error("Could not find Stuff in an inventory") {
}

void printDirection(Direction d) {
  switch (d) {
  case UP:
    std::cout << "UP";
    break;
  case UPRIGHT:
    std::cout << "UPRIGHT";
    break;
  case RIGHT:
    std::cout << "RIGHT";
    break;
  case RIGHTDOWN:
    std::cout << "RIGHTDOWN";
    break;
  case DOWN:
    std::cout << "DOWN";
    break;
  case DOWNLEFT:
    std::cout << "DOWNLEFT";
    break;
  case LEFT:
    std::cout << "LEFT";
    break;
  case LEFTUP:
    std::cout << "LEFTUP";
    break;
  case STOP:
    std::cout << "STOP";
    break;
  case ERROR:
    std::cout << "ERROR";
  default:
    std::cout << "printDirection : error";
  }
}

Player::Player(int pid, float xx, float yy) {
  position = Position(xx, yy);
  this->d = Direction::STOP;
  this->playerID = pid;
  this->speed = 1.;
  lastTimeStamp = -1;
  //this->addItem(Knife());
  this->addItem(C_Knife());
  //this->addItem(Bomb(2));
  //this->addItem(Gun(5, 2, 4));
  //this->addItem(Ammunition(10));
}
;

Player::Player(const Player& other) {
  LOG(error) << "The copy constructor of Player should never be called.";
}
;

int Player::getID() {
  return this->playerID;
}
;

Direction Player::getDirection() {
  return this->d;
}
;

std::vector<int> Player::getInventory() {
  std::vector<int> ids;
  ids.resize(inventory.size());
  std::transform(inventory.begin(), inventory.end(), ids.begin(), [](std::unique_ptr<Clickable>& stuff) {
	  return stuff->ClickableID;});
  return ids;
}
;

void Player::setDirection(Direction newd, int timeStamp) {
  if (timeStamp > lastTimeStamp){
      assert(isServer != 0);

    std::cout << "Server : player " << this->playerID
	      << " changes direction from ";
    printDirection(this->d);
    std::cout << " to ";
    printDirection(newd);
    std::cout << "\n";
    this->d = newd;
    lastTimeStamp = timeStamp;
    return;
  }
  else{
    std::cout << "Server : player " << this->playerID << " reject changement of direction. Cause : bad timestamp " << lastTimeStamp << " " << timeStamp << std::endl;
  }
}
;

void Player::setDirection(Direction newd) {
  assert(isServer == 0);
  std::cout << "Client : player " << this->playerID
	    << " changes direction from ";
  
  printDirection(this->d);
  std::cout << " to ";
  printDirection(newd);
  std::cout << "\n";
  this->d = newd;
  return;
}
;

void Player::addItem(Clickable&& stuff) {
	this->inventory.push_back(std::unique_ptr<Clickable>(new Clickable(stuff)));
	DBG << "Add item to player " << this->playerID << " : " << stuff.name;
	return;
};

void Player::removeItem(int stuffID) {
  for (auto& stuffPtr : inventory) {
    if (stuffPtr->ClickableID == stuffID) {
      inventory.remove(stuffPtr);
      break;
    }
  }
  return;
}
;

void Player::updatePosition(sf::Time dt, Geography& map) {
  float dep = (this->speed) * (dt.asSeconds()) * SPEED_AMPLIFIER;
  float sqrttwo = 1.414213562;
  float x = position.getX();
  float y = position.getY();
  switch (this->d) {
  case UP:
    position.add(0, -dep);
    if (!(position.getX() > 0 && position.getX() < 10000 && position.getY() > 0
        && position.getY() < 10000)) {
      position.add(0, dep);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(0, dep);
    }
    break;
  case UPRIGHT:
    position.add(dep / sqrttwo, -dep / sqrttwo);
    if (!(position.getX() > 0 && position.getX() < 10000 && position.getY() > 0
        && position.getY() < 10000)) {
      position.add(-dep / sqrttwo, dep / sqrttwo);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(-dep / sqrttwo, dep / sqrttwo);
    }
    break;
  case RIGHT:
    position.add(dep, 0);
    if (!(position.getX() > 0 && position.getX() < 10000 && position.getY() > 0
        && position.getY() < 10000)) {
      position.add(-dep, 0);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(-dep, 0);
    }
    break;
  case RIGHTDOWN:
    position.add(dep / sqrttwo, dep / sqrttwo);
    if (!(position.getX() > 0 && position.getX() < 10000 && position.getY() > 0
        && position.getY() < 10000)) {
      position.add(-dep / sqrttwo, -dep / sqrttwo);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(-dep / sqrttwo, -dep / sqrttwo);
    }
    break;
  case DOWN:
    position.add(0, dep);
    if (!(position.getX() > 0 && position.getX() < 10000 && position.getY() > 0
        && position.getY() < 10000)) {
      position.add(0, -dep);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(0, -dep);
    }
    break;
  case DOWNLEFT:
    position.add(-dep / sqrttwo, dep / sqrttwo);
    if (!(position.getX() > 0 && position.getX() < 10000 && position.getY() > 0
        && position.getY() < 10000)) {
      position.add(dep / sqrttwo, -dep / sqrttwo);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(dep / sqrttwo, -dep / sqrttwo);
    }
    break;
  case LEFT:
    position.add(-dep, 0);
    if (!(position.getX() > 0 && position.getX() < 10000 && position.getY() > 0
        && position.getY() < 10000)) {
      position.add(dep, 0);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(dep, 0);
    }
    break;
  case LEFTUP:
    position.add(-dep / sqrttwo, -dep / sqrttwo);
    if (!(position.getX() > 0 && position.getX() < 10000 && position.getY() > 0
        && position.getY() < 10000)) {
      position.add(dep / sqrttwo, dep / sqrttwo);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(dep / sqrttwo, dep / sqrttwo);
    }
    break;
  case STOP:
    break;
  default:
    //ne doit pas arriver
    std::cerr << "Player::updatePosition : Direction not correct "
        << (int) (this->d) << "\n";
    break;
  };
  if (!(x == position.getX() && y == position.getY())) {
    DBG << position.getX() << " + " << position.getY();
  }
  return;
}
;

bool Player::hasItemByID(int ClickableID) {
	std::cout << ClickableID << std::endl;
	try {
    getItemByID<Clickable> (ClickableID);
    return true;
  } catch (const StuffNotFound& err) {
    return false;
  }
}
