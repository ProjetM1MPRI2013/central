/**
   @author: Marc B., Adrien K.
 */


#ifndef ACTIONPC_H
#define ACTIONPC_H


#include "../simulation/position.h"
#include "Clickable.h"
#include "Action.h"
class LocalState;

#define COST_COP1 1 //cout d'entretien d'un cop
#define COST_CAM1 1 //cout d'entretien d'une caméra
#define COST_COP2 1 //cout de placement d'un cop
#define COST_CAM2 1 //cout de placement d'une caméra

class AddCop : public Action {
 public:
  bool IsActionPossible ();
  void doAction();
  AddCop (int number, float x, float y, LocalState* s);
  AddCop(const AddCop&);

  virtual AbstractMessage* copy();


 private:
  int number;
  float x;
  float y;

private :
  //Serialization
  AddCop(){}

  SIMPLE_MESSAGE(AddCop, Action, number, x, y)

};
BOOST_CLASS_EXPORT_KEY(AddCop)


class AddCam : public Action {
 public:
  bool IsActionPossible ();
  void doAction();
  AddCam (int number,float x, float y, LocalState* s);
  AddCam(const AddCam&);
  
  virtual AbstractMessage* copy();
  
  
 private:
  int number;
  float x;
  float y;

private :
  //Serialization
  AddCam(){}

  SIMPLE_MESSAGE(AddCam, Action, number, x, y)
};

BOOST_CLASS_EXPORT_KEY(AddCam)

#endif
