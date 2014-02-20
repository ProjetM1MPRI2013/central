
//*@author Marc B,
#include <boost/serialization/export.hpp>

#include "ActionsPC.h"
#include "../simulation/simulation.h"
#include "globalState.h"
#include "localState.h"
#define DEBUG true
#include <debug.h>


bool :: AddCop::IsActionPossible() {return (COST_COP2 <= (this->simulation)->getSous());}
bool :: AddCam::IsActionPossible() {return (COST_CAM2 <= (this->simulation)->getSous());}

AddCop :: AddCop(int n,float xx, float yy, LocalState* s) : Action("AddCop",s) {
this->number = n;
this->x = xx;
this->y = yy;
}

AddCop::AddCop(const AddCop& a) : Action("AddCop",a.simulation){
  this->number = a.number;
  this->x = a.x;
  this->y = a.y;
}

AddCam :: AddCam(int n, float xx,float yy, LocalState* s, int typee) : Action("AddCam",s) {
	this->number = n;
	this->x  = xx;
	this->y = yy;
	this->type = typee;
}

AddCam::AddCam(const AddCam& a) : Action("AddCam",a.simulation){
  this->number = a.number;
  this->x = a.x;
  this->y = a.y;
  this->type = a.type;

}


void AddCam::doAction() {simulation->getClient()->sendMessage(*this,true);}
void AddCop::doAction() {simulation->getClient()->sendMessage(*this,true);}


//AbstractMessage methods implementation
AbstractMessage* AddCop::copy(){
  return (AbstractMessage*) new AddCop(*this);
}

AbstractMessage* AddCam::copy(){
  return (AbstractMessage*) new AddCam(*this);
}
