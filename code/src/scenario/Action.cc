#define DEBUG false
#include "debug.h"

#include "Action.h"
#include "ActionsPC.h"
#include "ActionsTerro.h"

#include "localState.h"

Action::Action(std::string n, LocalState* s) {
  name = n;
  simulation = s;
  this->playerID = this->simulation->getOwner().getID ();
}

Action::Action(const Action& a){
  this->name = a.name;
  this->simulation = a.simulation;
  this->playerID = a.playerID;
}

bool Action::isActionPossible(){
  std::cerr << "isActionPossible called but not implemented for the Action type :" << name << "\n";
  return 0;
}

void Action::doAction(){
  std::cerr << "doAction called but not implemented for the Action type :" << name << "\n";
  return;
}

void Action::addPendingActions(GlobalState* hs){
  std::cerr << "addPendingActions called but not implemented for the Action type :" << name << "\n";
  return;
}


Action::Action() : name(""), date(0), delay(0), simulation(NULL), playerID(0){}

// AbstractMessage function
AbstractMessage* Action::copy(){
  return ((AbstractMessage*)new Action(*this));
}
