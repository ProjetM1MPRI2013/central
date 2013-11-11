#include "trajectory.h"

//il manque le constructeur qui genere la trajectoire en tenant compte du plan de la ville
vector<Position> Trajectory::getPosList() {
  return posList;
}


void Trajectory::setPosList(Position p) {
  posList = p;
  return;
}


Position Trajectory::getCurrentPos() {
  return posList[0];
}

void Trajectory::updateTrajectory(sf::Time dt,float speed,Geography const& map) {
  float dist = dt.asSeconds()*speed;
  Position position = posList[0];
  Position objectif = posList[1];
  float dX = objectif.getX()-position.getX();
  float dY = objectif.getY()-position.getY();
  float norme = sqrt(pow(dirX,2)+pow(dirY,2));
  dX = dX/norme;
  dY = dY/norme;
  dX = dX*dist;
  dY = dY*dist;
  posList[0].add(dX,dY);
  return;
}  



