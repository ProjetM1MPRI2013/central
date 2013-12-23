#include "trajectory.h"
#include "../generation/tile.h"
#include "tilewrapper.h"

#include <vector>
#include <list>
#include <cassert>
#include <queue>

#define DEBUG false
Trajectory::Trajectory() {
  Position p1,p2;
  p1 = Position();
  p2 = Position();
  posList = std::list<Position> ();
  posList.push_front(p2);
  posList.push_front(p1);
  hasArrived = false;
  speed = std::pair<float,float>(0,0);
  acceleration = std::pair<float,float>(0,0);
  return;
}

Trajectory::Trajectory(Position start,Position target,Geography& map) {
  posList = std::list<Position> ();
  posList.push_front(target);
  posList.push_front(start);
  pathfinding(map);
  hasArrived = false;
  speed = std::pair<float,float>(0,0);
  acceleration = std::pair<float,float>(0,0);
  return;
}

Trajectory::Trajectory(Trajectory& t) {
  posList = std::list<Position>(t.getPosList());
  hasArrived = t.getHasArrived();
  speed = t.getSpeed();
  acceleration = t.getAcceleration();
  return;
  }


void Trajectory::explore(TileWrapper* y,TileWrapper* z,PriorityQueue& open) {
  if (!y->isClosed()) {
    if (y->isOpen()) {
      if (z->getDistance()+1<y->getDistance()) {
        y->setParent(z);
        y->setDistance(z->getDistance()+1);
        open.increase(y->getHandle());
      }
    } else {
      y->setOpen(true);
      y->setParent(z);
      y->setDistance(z->getDistance()+1);
      PriorityQueue::handle_type h = open.push(y);
      y->setHandle(h);
    }
  }
  return;
}

void Trajectory::pathfinding(Geography& map) {
  assert(posList.size()>1);//le vecteur doit contenir au moins le départ et l'arrivée
  Position start,target;
  start = posList.front();
  target = posList.back();
  posList.clear();
  
  PriorityQueue open;
  std::list<TileWrapper*> closed;

  Tile& tileStart = start.isInTile(map);
  Tile& tileTarget = target.isInTile(map);

  TileWrapper* s = new TileWrapper(&tileStart,tileTarget);
  s->setDistance(0);
  s->setOpen(true);
  PriorityQueue::handle_type h = open.push(s);
  s->setHandle(h);

  TileWrapper* t = new TileWrapper(&tileTarget,tileTarget);

  TileWrapper* temp;
  bool found = false;
  
  while (!open.empty() && !found) {
    TileWrapper* z = open.top();
    open.pop();
    if (z->equals(*t)) {
      temp = z;
      found = true;
    } else {
      z->setClosed(true);
      closed.push_front(z);

      std::list<Tile*> neighbourTiles = z->getTile().getNeighbourTiles(map);
      
      while (!neighbourTiles.empty()) {
        Tile* tempTile = neighbourTiles.front();
        neighbourTiles.pop_front();
        TileWrapper* y = tempTile->getWrapper();
        if (y) {
          explore(y,z,open);
        } else {
          y = new TileWrapper(tempTile,tileTarget);
          explore(y,z,open);
        }
      }
    }
  }
  if (!found) {
    printf("départ : %f %f, arrivée : %f %f\n",start.getX(),start.getY(),target.getX(),target.getY());
  }
  assert(found);//si la map est pas connexe voir avec Chatan
  
  posList.push_front(target);
  //temp n'est pas initialisé à priori, g++ râle. Il faudrait régler ça.
  while (!temp->equals(*s)) {
    temp = temp->getParent();
    assert(temp);
    posList.push_front(Position(temp->getTile()));
    if (DEBUG) {
      printf("pathfinding: tile %d %d position %f %f\n",temp->getTile().getCoord().getAbs(),temp->getTile().getCoord().getOrd(),posList.front().getX(),posList.front().getY());
    }
  }
  posList.pop_front();
  posList.push_front(start);

  tileTarget.resetWrapper();

  while(!open.empty()) {
    TileWrapper* tempWrapper = open.top();
    open.pop();
    tempWrapper->getTile().resetWrapper();
  }

  while(!closed.empty()) {
    TileWrapper* tempWrapper = closed.front();
    closed.pop_front();
    tempWrapper->getTile().resetWrapper();
  }
  return;
}
                
      
std::list<Position>& Trajectory::getPosList() {
  return posList;
}


Position& Trajectory::getPosition() {
  return posList.front();
}

void Trajectory::setPosition(Position& p) {
  posList.pop_front();
  posList.push_front(p);
  return;
}

bool Trajectory::getHasArrived() {
  return hasArrived;
}

void Trajectory::update(sf::Time dt,float speedNorm,Geography& map) {
  assert(!posList.empty());//il doit y avoir au moins la position courante  
  if (!hasArrived) {//si on n'est pas arrivé : on avance en ligne droite
    assert(posList.size()>1);//il doit y avoir la position courante et au moins un objectif
    float dist = dt.asSeconds()*speedNorm;//distance parcourue en dt à la vitesse normSpeed
    Position position = posList.front();
    posList.pop_front();
    Position& target = posList.front();

    //update the position p(t) -> p(t+dt) = p(t)+dt*s(t)
    float dX = speed.first*dt.asSeconds();
    float dY = speed.second*dt.asSeconds();
    position.add(dX,dY);
    if (position.getX()>=map.getMapWidth()) {
      position.setX(map.getMapWidth()-0.5);
    }
    if (position.getX()<0) {
      position.setX(0.5);
    }
    if (position.getY()>=map.getMapHeight()) {
      position.setY(map.getMapHeight()-0.5);
    }
    if (position.getY()<0) {
      position.setY(0.5);
    }

    //update the speed s(t) -> s(t+dt) = s(t)+dt*a(t)
    speed.first += acceleration.first * dt.asSeconds();
    speed.second += acceleration.second * dt.asSeconds();
    //speed is capped by speedNorm
    float speedNorm2 = sqrt(pow(speed.first,2)+pow(speed.second,2));
    if (speedNorm2 > speedNorm) {
      speed.first = speed.first * speedNorm/speedNorm2;
      speed.second = speed.second * speedNorm/speedNorm2;
    }
    
    //update the acceleration a(t) -> a(t+dt) = 1/tau * (v0(t+dt)-v(t+dt))
    float v0X = target.getX()-position.getX();
    float v0Y = target.getY()-position.getY();
    float norm = (float)sqrt(pow(v0X,2)+pow(v0Y,2));
    if (norm>0) {
      v0X = v0X*speedNorm/norm;
      v0Y = v0Y*speedNorm/norm;
    }
    acceleration.first = 1/tau * (v0X - speed.first);
    acceleration.second = 1/tau * (v0Y - speed.second);

    
    float dist1 = position.distance(target);
    
    if (dist1 <= dist/2) {//on est assez proche de l'objectif
      posList.pop_front();
      if (posList.empty()) {//il ne reste plus que la position courante
        hasArrived = true;
        if (DEBUG) {
          printf("NPC: arrived !\n");
        }
      } else {
        if (DEBUG) {
          printf("NPC: new target: %f %f, current position: %f %f\n",posList.front().getX(), posList.front().getY(),position.getX(),position.getY());
        }
      }
    }
    posList.push_front(position);
  }
  return;
}
