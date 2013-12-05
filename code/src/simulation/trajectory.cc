#include "trajectory.h"
#include "../generation/tile.h"

#include <vector>
#include <cassert>

Trajectory::Trajectory() {
  Position p1,p2;
  p1 = Position();
  p2 = Position();
  posList = std::vector<Position> ();
  posList.push_back(p1);
  posList.push_back(p2);
  hasArrived = false;
  return;
}

Trajectory::Trajectory(Position start,Position target,Geography& map) {
  posList = std::vector<Position> ();
  posList.push_back(start);
  posList.push_back(target);
  pathfinding(map);
  hasArrived = false;
  return;
}

Trajectory::Trajectory(Trajectory& t) {
  posList = std::vector<Position>(t.getPosList());
  hasArrived = t.getHasArrived();
  return;
}


void Trajectory::pathfinding(Geography& map) {//stupide pour l'instant, A* apres
  assert(posList.size()>1);//le vecteur doit contenir au moins le départ et l'arrivée
  Position start,target;
  start = posList[0];
  target = posList[posList.size()-1];
  posList.clear();
  posList.push_back(start);
  posList.push_back(target);
  return;
}

std::vector<Position>& Trajectory::getPosList() {
  return posList;
}


Position& Trajectory::getPosition() {
  return posList[0];
}

void Trajectory::setPosition(Position& p) {
  posList[0] = p;
  return;
}

bool Trajectory::getHasArrived() {
  return hasArrived;
}

void Trajectory::update(sf::Time dt,float speed,Geography& map) {
  assert(!posList.empty());//il doit y avoir au moins la position courante  
  if (!hasArrived) {//si on n'est pas arrivé : on avance en ligne droite
    assert(posList.size()>1);//il doit y avoir la position courante et au moins un objectif
    float dist = dt.asSeconds()*speed;
    Position& position = posList[0];
    Position& target = posList[1];
    float dX = target.getX()-position.getX();
    float dY = target.getY()-position.getY();
    float norm = (float)sqrt(pow(dX,2)+pow(dY,2));
    dX = dX/norm;
    dY = dY/norm;
    dX = dX*dist;
    dY = dY*dist;
    posList[0].add(dX,dY);
    
    float dist1 = posList[0].distance(posList[1]);
    
    if (dist1 <= dist/2) {//on est assez proche de l'objectif
      posList.erase(posList.begin()+1);
      if (posList.size()<2) {//il ne reste plus que la position courante
        hasArrived = true;
      }
    }
  }
  return;
}
