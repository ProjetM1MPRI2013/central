#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <list>
#include <string>
#include "ActionType.h"

class Clickable {
 public:
  virtual std::list<ActionType> getActionPossible () = 0;
};

#endif
