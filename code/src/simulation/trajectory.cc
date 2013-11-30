#include "trajectory.h"
#include "../generation/tile.h"

#include <vector>

Trajectory::Trajectory() {
  Position p1,p2;
  p1 = Position();
  p2 = Position();
  Trajectory(p1,p2);
  return;
}

Trajectory::Trajectory(Position& start,Position& target) {
  posList = std::vector<std::reference_wrapper<Position>> (3,start);
  posList[1] = std::ref(start);
  posList[2] = std::ref(target);
  arrived = false;
  return;
}

Trajectory::Trajectory(Trajectory& t) {
  posList = std::vector<std::reference_wrapper<Position>>(t.getPosList());
  arrived = false;
  return;
}

std::vector<std::reference_wrapper<Position>>& Trajectory::getPosList() {
  return posList;
}


Position& Trajectory::getPosition() {
  return posList[0];
}

bool Trajectory::getArrived() {
  return arrived;
}

Tile& Trajectory::findNextTile(Tile& start,Tile& target) {
  return target;//temporaire, après il y aura le pathfinder à la place
}


void Trajectory::update(sf::Time dt,float speed,Geography& map) {
  /*on calcule la nouvelle position en avancant en ligne droite*/
  if (!arrived) {//du moins s'il n'est pas arrivé, sinon on ne fait rien
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
    ((Position)posList[0]).add(dX,dY);
    
    float dist1 = ((Position)posList[0]).distance(posList[1]);
    float dist2 = ((Position)posList[0]).distance(posList[2]);
    
    if (dist1 <= dist/2) {//on est assez proche de l'objectif à court terme
      if (dist2<=dist/2) {//et aussi de celui à long terme -> on est arrivé
        arrived = true;
      } else {//on a atteint l'objectif proche mais pas l'autre
        Tile& nextTile = findNextTile(((Position)posList[0]).isInTile(map),((Position)posList[2]).isInTile(map));
        Position p1;
        p1 = Position(nextTile);
        posList[1] = std::ref(p1);
      }
    }
  }
  return;
}



