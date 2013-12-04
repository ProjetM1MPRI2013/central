#include "ScenarioActionList.h"


/*****************
 *ChangeDirection*
 *****************/

class Couple {
public:
  int x;
  int y;
  Couple (int x, int y);
};

Couple::Couple (int a, int b){
  x = a;
  y = b;
};

Couple* directionToInt(Direction a){
  switch (a){
  case UP :
    return new Couple(0,1);
  case UPRIGHT :
    return new Couple(1,1);    
  case RIGHT:
    return new Couple(1,0);    
  case RIGHTDOWN :
    return new Couple(1,-1);    
  case DOWN :
    return new Couple(0,-1);    
  case DOWNLEFT :
    return new Couple(-1,-1);    
  case LEFT :
    return new Couple(-1,0);    
  case LEFTUP :
    return new Couple(-1,1);   
  case STOP :
    return new Couple(0,0);
  };
  //ne doit pas arriver
  std::cerr << "ScenarioActionList::directionToInt : Direction not correct " << (int) a << "\n";
  return new Couple (10,10);
};

Couple* newMovToInt(NewMov a){
  switch (a){
  case NewMov::R_UP :
    return new Couple (0,-1);
  case NewMov::R_DOWN :
    return new Couple (0,1);
  case NewMov::R_LEFT :
    return new Couple (1,0);
  case NewMov::R_RIGHT :
    return new Couple (-1,0);
  case NewMov::P_UP :
    return new Couple (0,1);
  case NewMov::P_DOWN :
    return new Couple (0,-1);
  case NewMov::P_LEFT :
    return new Couple (-1,0);
  case NewMov::P_RIGHT :
    return new Couple (1,0);
  };
  std::cerr << "ScenarioActionList::newMovToInt : Direction not correct " << (int) a << "\n";
  return new Couple (10,10);
};

Direction intToDirection(Couple* a){
  if ((a->x == 0)&&(a->y == 1)) {return Direction::UP;};
  if ((a->x == 1)&&(a->y == 1)) {return Direction::UPRIGHT;};
  if ((a->x == 1)&&(a->y == 0)) {return Direction::RIGHT;};
  if ((a->x == 1)&&(a->y == -1)) {return Direction::RIGHTDOWN;};
  if ((a->x == 0)&&(a->y == -1)) {return Direction::DOWN;};
  if ((a->x == -1)&&(a->y == -1)) {return Direction::DOWNLEFT;};
  if ((a->x == -1)&&(a->y == 0)) {return Direction::LEFT;};
  if ((a->x == -1)&&(a->y == 1)) {return Direction::LEFTUP;};
  if ((a->x == 0)&&(a->y == 0)) {return Direction::STOP;};
  //ne doit pas arriver
  std::cerr << "ScenarioActionList::intToDirection : Couple not correct " << a->x << " " << a->y << "\n";
  return Direction::STOP;
};

ChangeDirection::ChangeDirection(int id, NewMov mov) : ScenarioAction ("ChangeDirection"){
  playerID = id;
  newMovement = mov;
};

void ChangeDirection::run(){
  Direction a = simulation->getPlayerByID(playerID)->getDirection();
  Couple* b = directionToInt(a);
  Couple* c = newMovToInt(this->newMovement);
  Couple* newDir = new Couple(b->x + c->x, b->y + c->y);
  simulation->getPlayerByID(playerID)->setDirection(intToDirection(newDir));
  delete b;
  delete c;
  delete newDir;
  return;
};

/***********
 *Explosion*
 ***********/
Explosion::Explosion(Tile* t,int p) : ScenarioAction("Explosion"){
  location = t;
  power = p;
};

void Explosion::run(){
  return;
};

/*********
 *KillNPC*
 *********/
KillNPC::KillNPC(NPC* t) : ScenarioAction("KillNPC"){
  target = t;
};

void KillNPC::run(){
  //Supprime un NPC de la case du NPC target, vue qu'il n'existe pas de methode pour supprimer un NPC précis -_-' [Adrien K]
  //TODO : gérer le cas ou le NPC n'existe pas
    simulation->supprimerNPC(simulation->isInTileX(target),simulation->isInTileY(target));
  return;
};
