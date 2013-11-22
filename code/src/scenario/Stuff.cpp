#include "Stuff.h"

int Stuff::counter = 0;

std::list<std::string> Stuff::getActionsPossible () {return actionsPossible;};

Stuff::Stuff (std::string n) {
  name = n;

  /* This is not an atomic operation. 
   * This should not create bug since only the simulation will creates new objects.
   */
  stuffID = counter;
  counter = counter + 1;

  this->actionsPossible = list<std::string>;
  this->actionsPossible.push_back("DropStuff");
};
