/**
   @author: Marc B., Adrien K.
 */


#ifndef ACTIONPC_H
#define ACTIONPC_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>

#include "../simulation/position.h"
#include "Clickable.h"
#include "Action.h"
#include "../simulation/simulation.h"

#define COST_COP1 1 //cout d'entretien d'un cop
#define COST_CAM1 1 //cout d'entretien d'une caméra
#define COST_COP2 1 //cout de placement d'un cop
#define COST_CAM2 1 //cout de placement d'une caméra

class AddCop : public Action {
 public:
  bool IsActionPossible ();
  void doAction();
  AddCop (int number, float x, float y, Simulation* s);
  AddCop(const AddCop&);

  //AbstractMessage functions
  //virtual std::string & toString();
  //static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();


 private:
  int number;
  float x;
  float y;

private :
  //Serialization
  AddCop(){}
  friend class boost::serialization::access ;

  template <class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & boost::serialization::base_object<Action>(*this);
    ar & number ;
    ar & x ;
    ar & y ;
  }

};

class AddCam : public Action {
 public:
  bool IsActionPossible ();
  void doAction();
  AddCam (int number,float x, float y, Simulation* s);
  AddCam(const AddCam&);
  
  //AbstractMessage functions
  //virtual std::string & toString();
  //static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();
  
  
 private:
  int number;
  float x;
  float y;

private :
  //Serialization
  AddCam(){}
  friend class boost::serialization::access ;

  template <class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & boost::serialization::base_object<Action>(*this);
    ar & number ;
    ar & x ;
    ar & y ;
  }
  
};












#endif
