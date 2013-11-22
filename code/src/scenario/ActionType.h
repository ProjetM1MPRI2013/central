#ifndef ACTIONTYPE_H
#define ACTIONTYPE_H

#include "Action.h"
#include <string>

class ActionType {
 public:
  std::string name;
  ActionType (std::string n);
  virtual Action doAction (void* parameters[]) = 0;
  virtual int isPossible (void* parameters[]) = 0;
};

#endif
