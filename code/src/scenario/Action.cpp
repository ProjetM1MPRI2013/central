#include <cerrno>
#include <iostream>
#include "Action.h"

Action::Action(std::string n) {
  name = n;
  playerID = "";
};

Action::isActionPossible(){
  std::cerr << "isActionPossible called but not implemented for the Action type :" << this.name << "\n";
  return 0;
};

Action::doAction(){
  std::cerr << "doAction called but not implemented for the Action type :" << this.name << "\n";
return;
};
