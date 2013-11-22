#include "Stuff.h"

int Stuff::counter = 0;

std::list<ActionType> Stuff::getActionPossible () {return actionPossible;};

Stuff::Stuff (std::string n) {
  name = n;
  stuffID = counter;
  counter = counter + 1;
  actionPossible = new list<ActionType>;
  actionPossible.push_back((ActionType) (new DropStuff ()));
};

class Weapon : public Stuff {
public:
  Weapon (): Stuff ("Weapon") {
    actionPossible.push_back((ActionType) (new DropStuff()));
  };
};
