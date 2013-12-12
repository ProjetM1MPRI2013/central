#include "Action.h"

Action::Action(std::string n, Simulation* s) {
  name = n;
  simulation = s;
  this->playerID = this->simulation->getPlayer()->getID ();
};

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
