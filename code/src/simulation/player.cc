#include <algorithm>
#include "player.h"
#include <cmath>
#include "scenario/Stuff.h"
#include "scenario/StuffList.h"
#include "game_textures.h"

#define SPEED_AMPLIFIER 8

#define DEBUG false
#include "debug.h"


StuffNotFound::StuffNotFound() :
  std::runtime_error("Could not find Stuff in an inventory") {
}

std::string stringMovementType(MovementType m) {
  switch (m) {
    case DIRECTION: return "DIRECTION";
    case DESTINATION: return "DESTINATION";
    default: return "stringMovementType: error";
  }
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

Player::Player(int pid, float xx, float yy) : Positionable(xx,yy), DrawableObject(textures::get(0)) {
  this->movementType = DIRECTION;
  this->destination = Position();
  this->d = Direction::STOP;
  this->playerID = pid;
  this->speed = 1.;
  lastTimeStamp = -1;
  this->addItem(C_Knife());
  this->addItem(C_Bomb(2));
  this->addItem(C_Gun(5, 2., 4));
  this->addItem(C_Ammunition(10));
  this->addItem(C_UltraM());
 // this->addItem(C_Flower());

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
    this->movementType = DIRECTION;
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
  this->movementType = DIRECTION;
  return;
}
;

void Player::setDestination(Position pos, int timeStamp) {
  if (timeStamp > lastTimeStamp){
      assert(isServer != 0);

    DBG << "Server : player " << this->playerID << " changes destination to " << pos;
    
    this->destination = pos;
    this->movementType = DESTINATION;
    lastTimeStamp = timeStamp;
    return;
  }
  else{
    DBG << "Server : player " << this->playerID << " reject changement of destination. Cause : bad timestamp " << lastTimeStamp << " " << timeStamp;
  }
}
;

void Player::setDestination(Position pos) {
  assert(isServer == 0);
  this->destination = pos;
  this->movementType = DESTINATION;
}

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
  float x = position.getX();
  float y = position.getY();

  if (movementType == DESTINATION) {

    if (destination.distance(position) < 0.4) {
      DBG << "__________________________";
       
      movementType = DIRECTION;
    } else {
      float dX = destination.getX() - x;
      float dY = destination.getY() - y;
      float aX = fabs(dX);
      float aY = fabs(dY);
      DBG << "Destination-based move:";
      DBG << "  pos     : " << position;
      DBG << "  dest    : " << destination;
      DBG << "  abs     : " << dX << "/" << aX << " " << dY << "/" << aY;
      DBG << "  x/y/spd : " << (dX/(aX+aY)) << "/" <<  (dY/(aX+aY)) << "/" << dep;
      position.add(dep * (dX/(aX+aY)), dep * (dY/(aX+aY)));
      DBG << "  pos'    : " << position;
    }

  } else {

  float sqrttwo = 1.414213562;
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
