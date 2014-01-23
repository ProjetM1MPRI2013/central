#include "Action.h"

Action::Action(std::string n, Simulation* s) {
  name = n;
  simulation = s;
  this->playerID = this->simulation->getPlayer()->getID ();
};

Action::Action(const Action& a){
  this->name = a.name;
  this->simulation = a.simulation;
  this->playerID = a.playerID;
}

bool Action::isActionPossible(){
  std::cerr << "isActionPossible called but not implemented for the Action type :" << name << "\n";
  return 0;
};

void Action::doAction(){
  std::cerr << "doAction called but not implemented for the Action type :" << name << "\n";
  return;
};

void Action::addPendingActions(HostSimulation* hs){
  std::cerr << "addPendingActions called but not implemented for the Action type :" << name << "\n";
  return;
}


//AbstractMessage function implementations
std::string Action::getMsgType(){
  std::string s = "C_ACTION";
  return s;
}

std::string Action::toString(){
  std::string s = "TODO";
  return s;
}

AbstractMessage* Action::fromString(std::string& msg){
  return ((AbstractMessage*)new Action("TODO", NULL));
}

AbstractMessage* Action::copy(){
  return ((AbstractMessage*)new Action(*this));
}
