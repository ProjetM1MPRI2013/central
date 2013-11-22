#include "Action.h"
#include "Stuff.h"

class Action{
  Action(std::string n) {
    name = n;
  };
};



class ADropStuff: public Action {
public:
  int stuffID;
  ADropStuff (Stuff* s): Action ("ADropStuff") {
    stuffID = s->stuffID;
  };
};
