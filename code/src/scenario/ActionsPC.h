/**
  // @author: Marc B., Adrien K.
 */


#ifndef ACTIONPC_H
#define ACTIONPC_H


#include "../simulation/position.h"
#include "Action.h"
class LocalState;

#define COST_COP1 1 //cout d'entretien d'un cop
#define COST_CAM1 1 //cout d'entretien d'une caméra
#define COST_COP2 1 //cout de placement d'un cop
#define COST_CAM2 1 //cout de placement d'une caméra
#define COST_CAM2_2 2 //cout de placement d'une caméra#Swag
#define COST_CAM1_2 2 //cout de placement d'une caméra#SWAG


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


class AddCam : public Action {
 public:
  bool IsActionPossible ();
  void doAction();
  AddCam (int number,float x, float y, LocalState* s,int type);
  AddCam(const AddCam&);
  
  virtual AbstractMessage* copy();
  
  
 private:
  int number;
  float x;
  float y;
  int type;



  //Serialization
  AddCam(){}

  SIMPLE_MESSAGE(AddCam, Action, number, x, y)
};


#endif
