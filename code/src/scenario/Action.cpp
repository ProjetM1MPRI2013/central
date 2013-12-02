#include <cerrno>
#include <iostream>
#include "Action.h"

Action::Action(std::string n) {
  name = n;
  this->playerID = ""; /* to do find the player id*/
};

bool Action::isActionPossible(){
  std::cerr << "isActionPossible called but not implemented for the Action type :" << name << "\n";
  return 0;
};

void Action::doAction(){
  std::cerr << "doAction called but not implemented for the Action type :" << name << "\n";
  return;
};

/*  to check */

void Action::doAction(){

}

