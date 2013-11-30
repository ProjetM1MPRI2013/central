#ifndef POSITIONABLE_H
#define POSITIONABLE_H
#include "position.h"

class Positionable {
 private:
  Position position;
 public:
  Positionable();
  Positionable(float x,float y);
  Positionable(Position& p);
  virtual Position& getPosition()=0;
  virtual void setPosition(Position& p);
};
#endif
