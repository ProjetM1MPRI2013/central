#ifndef NEWMOV_H
#define NEWMOV_H

#include "network/abstractMessage.h"

enum NewMov {P_RIGHT, P_LEFT, P_UP, P_DOWN, R_RIGHT, R_LEFT, R_UP, R_DOWN};

void printNewMov(NewMov nm);

class NewMovNetwork : public AbstractMessage {
 public:
  NewMov movement;
  int playerID;
  NewMovNetwork(NewMov m, int pid);

  //AbstractMessage functions
  static std::string getMsgType();
  virtual std::string & toString();
  static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();
};

#endif
