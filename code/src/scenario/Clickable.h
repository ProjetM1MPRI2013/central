#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <list>
#include <string>

class Clickable {
 public:
  virtual std::list<std::string> getActionPossible ();
};

#endif
