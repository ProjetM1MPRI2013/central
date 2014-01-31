/**
   @author: Adrien K.
 */


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

  virtual AbstractMessage* copy();

protected :
  //Serialization

  NewMovNetwork() ;

  SIMPLE_MESSAGE(NewMovNetwork, AbstractMessage, movement, playerID)
};

BOOST_CLASS_EXPORT_KEY(NewMovNetwork)
#endif
