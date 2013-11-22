#ifndef STUFF_H
#define STUFF_H

#include <list>
#include <string>
#include "Clickable.h"
#include "ActionType.h"

class Stuff : public Clickable {
 public :
  std::string name;
  int stuffID;
  virtual std::list<ActionType> getActionPossible ();
  Stuff (std::string n);
 protected:
  std::list<ActionType> actionPossible;
 private:
  static int counter;
};

#endif
