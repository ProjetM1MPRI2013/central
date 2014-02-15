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

std::string stringDirection(Direction d) {
  switch (d) {
  case UP:
    return "UP";
    break;
  case UPRIGHT:
    return "UPRIGHT";
    break;
  case RIGHT:
    return "RIGHT";
    break;
  case RIGHTDOWN:
    return "RIGHTDOWN";
    break;
  case DOWN:
    return "DOWN";
    break;
  case DOWNLEFT:
    return "DOWNLEFT";
    break;
  case LEFT:
    return "LEFT";
    break;
  case LEFTUP:
    return "LEFTUP";
    break;
  case STOP:
    return "STOP";
    break;
  case ERROR:
    return "ERROR";
  default:
    return "stringDirection : error";
  }
}

Player::Player(int pid, float xx, float yy) {
  position = Position(xx, yy);
  this->d = Direction::STOP;
  this->playerID = pid;
  this->speed = 1.;
  lastTimeStamp = -1;
  this->addItem(C_Knife());
  this->addItem(C_Bomb(2));
  this->addItem(C_Gun(5, 2, 4));
  this->addItem(C_Ammunition(10));
  this->addItem(C_UltraM());
}
;

Player::Player(const Player& other) {
  LOG(error) << "The copy constructor of Player should never be called.";
}
;

int Player::getID() const {
  return this->playerID;
}
;

Direction Player::getDirection() const {
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

    DBG << "Server : player " << this->playerID << " changes direction from " << stringDirection(this->d) << " to " << stringDirection(newd);
    
    this->d = newd;
    lastTimeStamp = timeStamp;
    return;
  }
  else{
    DBG << "Server : player " << this->playerID << " reject changement of direction. Cause : bad timestamp " << lastTimeStamp << " " << timeStamp;
  }
}
;

void Player::setDirection(Direction newd) {
  assert(isServer == 0);
  DBG << "Client : player " << this->playerID << " changes direction from " << stringDirection(this->d) << " to " << stringDirection(newd); 
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
    if (!(position.getX() > 0 && position.getX() < (map.getMapWidth()) && position.getY() > 0
        && position.getY() < (map.getMapHeight()))) {
      position.add(0, dep);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(0, dep);
    }
    break;
  case UPRIGHT:
    position.add(dep / sqrttwo, -dep / sqrttwo);
    if (!(position.getX() > 0 && position.getX() < (map.getMapWidth()) && position.getY() > 0
        && position.getY() < (map.getMapHeight()))) {
      position.add(-dep / sqrttwo, dep / sqrttwo);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(-dep / sqrttwo, dep / sqrttwo);
    }
    break;
  case RIGHT:
    position.add(dep, 0);
    if (!(position.getX() > 0 && position.getX() < (map.getMapWidth()) && position.getY() > 0
        && position.getY() < (map.getMapHeight()))) {
      position.add(-dep, 0);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(-dep, 0);
    }
    break;
  case RIGHTDOWN:
    position.add(dep / sqrttwo, dep / sqrttwo);
    if (!(position.getX() > 0 && position.getX() < (map.getMapWidth()) && position.getY() > 0
        && position.getY() < (map.getMapHeight()))) {
      position.add(-dep / sqrttwo, -dep / sqrttwo);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(-dep / sqrttwo, -dep / sqrttwo);
    }
    break;
  case DOWN:
    position.add(0, dep);
    if (!(position.getX() > 0 && position.getX() < (map.getMapWidth()) && position.getY() > 0
        && position.getY() < (map.getMapHeight()))) {
      position.add(0, -dep);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(0, -dep);
    }
    break;
  case DOWNLEFT:
    position.add(-dep / sqrttwo, dep / sqrttwo);
    if (!(position.getX() > 0 && position.getX() < (map.getMapWidth()) && position.getY() > 0
        && position.getY() < (map.getMapHeight()))) {
      position.add(dep / sqrttwo, -dep / sqrttwo);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(dep / sqrttwo, -dep / sqrttwo);
    }
    break;
  case LEFT:
    position.add(-dep, 0);
    if (!(position.getX() > 0 && position.getX() < (map.getMapWidth()) && position.getY() > 0
        && position.getY() < (map.getMapHeight()))) {
      position.add(dep, 0);
    }
    if (!((position.isInTile(map)).isWalkable())) {
      position.add(dep, 0);
    }
    break;
  case LEFTUP:
    position.add(-dep / sqrttwo, -dep / sqrttwo);
    if (!(position.getX() > 0 && position.getX() < (map.getMapWidth()) && position.getY() > 0
        && position.getY() < (map.getMapHeight()))) {
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
    LOG(error) << "Player::updatePosition : Direction not correct " << (int) (this->d);
    break;
  };
  if (!(x == position.getX() && y == position.getY())) {
    DBG << position.getX() << " + " << position.getY();
  }
  return;
}
;

bool Player::hasItemByID(int ClickableID) {
  
	DBG << ClickableID;
	try {
    getItemByID<Clickable> (ClickableID);
    return true;
  } catch (const StuffNotFound& err) {
    return false;
  }
}
