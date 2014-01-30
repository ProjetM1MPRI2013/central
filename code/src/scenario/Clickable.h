/**
   @author: Adrien K.
 */


#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <list>
#include <string>

class Clickable {
 public:
  virtual std::list<std::string> getActionPossible () = 0;
};

#endif
