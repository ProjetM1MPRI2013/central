#include "ActionType.h"
#include "Stuff.h"

class ActionType {
  ActionType (std::string n) {
    name = n;
  };
};


class DropItem: public ActionType {
public:
  DropItem () : ActionType ("DropItem") {
  };
  Action doAction (void* parameters[]) {
    return (Action) (new ADropItem ((Stuff*) parameters[0]));
  };
  int isPossible (void* parameters[]) {
    return true;
  };
};
