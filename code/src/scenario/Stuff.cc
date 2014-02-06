#include "Stuff.h"
#include "ActionsTerro.h"

int Clickable::counter = 0;

Clickable::Clickable () {

  /* This is not an atomic operation.
   * This should not create bug since only the simulation will creates new objects.
   */
  ClickableID = counter;
  counter = counter + 1;
  std::list<SoN> l_drop ;
  std::list<ActionType> ActionTypePossible;
};

Clickable::Clickable (std::string n) {
  name = n;

  /* This is not an atomic operation. 
   * This should not create bug since only the simulation will creates new objects.
   */
  ClickableID = counter;
  counter = counter + 1;
  std::list<SoN> l_drop ;
  std::list<ActionType> ActionTypePossible;
};


Clickable::Clickable (std::string n, int id){
  name = n;
  ClickableID = id;
  std::list<SoN> l_drop ;
  std::list<ActionType> ActionTypePossible ;

};


std::list<ActionType> Clickable::getActionTypePossible () {return this->ActionTypePossible;};
