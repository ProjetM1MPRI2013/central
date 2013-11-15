#include "Stuff.h"

class Action {
public : 
  string name;
  Stuff* objectUsed;
  Action () {}
};


class Cut : public Action {
  NPC* target;
  Cut (Stuff* stuff, NPC* t) {
    name = "cut";
    objectUsed = stuff;
    target = t;
  }
};

class Fire : public Action {
  NPC* target;
  Cut (Stuff* stuff, NPC* t) {
    name = "fire";
    objectUsed = stuff;
    target = t;
  }
};

class AddSilencer : public Action {
  Stuff* firearme;
  AddSilencer (Stuff* silencer, Stuff* f) {
    name = "add silencer";
    objecUsed = silencer;
    firearme = f;
  }
};

class RemoveSilencer : public Action {
  RemoveSilencer (Stuff* f) {
    name = "remove silencer";
    objecUsed = f;
  }
};

class 
