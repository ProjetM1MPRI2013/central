#include "ActionsPC.h"
#include "../simulation/simulation.h"



bool :: AddCop::IsActionPossible() {return (COST_COP2 <= (*simulation).getSous());};
bool :: AddCam::IsActionPossible() {return (COST_CAM2 <= (*simulation).getSous());};

AddCop :: AddCop(int n,float xx, float yy, Simulation* s) : Action("AddCop",s) {
this->number = n;
this->x = xx;
this->y = yy;
};

AddCam :: AddCam(int n, float xx,float yy, Simulation* s) : Action("AddCam",s) {
	this->number = n;
	this->x  = xx;
	this->y = yy;
};


void AddCam::doAction() {return;};
void AddCop::doAction() {return;};
