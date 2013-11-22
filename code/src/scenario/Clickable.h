#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <list>
#include <string>
#include "ActionType.h"

class Clickable {
 public:
  virtual std::list<std::string> getActionPossible () = 0;
};

#endif
