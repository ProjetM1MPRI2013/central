#include "Stuff.h"
#include "Action.h"
#include "ActionsTerro.h"






int Stuff::counter = 0;


std::list<ActionType*> Stuff::getActionTypePossible () {return ActionTypePossible;};

Stuff::Stuff (std::string n) {
  name = n;

  /* This is not an atomic operation. 
   * This should not create bug since only the simulation will creates new objects.
   */
  stuffID = counter;
  counter = counter + 1;
  std::list<SoN> l_drop ;
  ActionType* A_drop = new ActionType  ("drop",l_drop);
  this->ActionTypePossible.push_back(A_drop);
};


Stuff::Stuff (std::string n, int id){
  name = n;
  
  stuffID = id;
  std::list<SoN> l_drop ;
  ActionType* A_drop = new ActionType  ("drop",l_drop);
  this->ActionTypePossible.push_back(A_drop);
};
