/**
   @author: Adrien K.
 */


#ifndef NEWMOV_H
#define NEWMOV_H

class LocalState;

#include "network/abstractMessage.h"

enum NewMov {P_RIGHT, P_LEFT, P_UP, P_DOWN, R_RIGHT, R_LEFT, R_UP, R_DOWN};
enum Direction {UP, UPRIGHT, RIGHT, RIGHTDOWN, DOWN, DOWNLEFT, LEFT, LEFTUP, STOP, ERROR};

void printNewMov(NewMov nm);

class NewMovNetwork : public AbstractMessage {
 public:
  Direction newDirection;
  int playerID;

  /**
   * @brief the timeStamp of the new movement, in case of re-ordering by the network
   */
  int timeStamp;
  
  NewMovNetwork(NewMov m, int pid, LocalState* ls);

  virtual AbstractMessage* copy();

protected :
  /**
   * @brief used to generates unique incressing timestamps
   */
  static int counter;
  //Serialization

  NewMovNetwork() ;

  SIMPLE_MESSAGE(NewMovNetwork, AbstractMessage, newDirection, playerID, timeStamp)
};

#endif
