#include "NewMov.h"
#include <iostream>
#include "localState.h"
#include "ScenarioActionList.h"
#include "debug.h"

#define DEBUG true

int NewMovNetwork::counter = 1;

std::string stringNewMov(NewMov nm){
  switch (nm){
  case P_RIGHT:
    return "P_RIGHT";
    break;
  case P_LEFT:
    return "P_LEFT";
    break;
  case P_UP:
   return "P_UP";
    break;
  case P_DOWN:
   return "P_DOWN";
    break;
  case R_RIGHT:
   return "R_RIGHT";
    break;
  case R_LEFT:
   return "R_LEFT";
    break;
  case R_UP:
   return "R_UP";
    break;
  case R_DOWN:
   return "R_DOWN";
    break;
  default:
    return "Unknown NewMov";
    break;
  }
}

NewMovNetwork::NewMovNetwork(NewMov m, int pid, LocalState* ls){
  Direction a = ls->getOwner().getDirection();
  Couple* b = directionToInt(a);
  Couple* c = newMovToInt(m);
  Couple* newDir = new Couple(b->x + c->x, b->y + c->y);
  Direction d = intToDirection(newDir);
  this->newDirection = d;
  delete b;
  delete c;
  delete newDir;

  this->playerID = pid;
  timeStamp = counter++;
}


AbstractMessage* NewMovNetwork::copy(){
  return ((AbstractMessage*) new NewMovNetwork(*this));
}


NewMovNetwork::NewMovNetwork() : newDirection(STOP), playerID(0), timeStamp(counter++) {}
