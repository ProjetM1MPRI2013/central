#ifndef ACTIONPC_H
#define ACTIONPC_H

#include "../simulation/position.h"
#include "Clickable.h"
#include "Action.h"
#include "../simulation/simulation.h"

#define COST_COP 1
#define COST_CAM 1
#define COST_COP2 1
#define COST_CAM2 1

class AddCop : public Action {
public:
	bool IsActionPossible ();
	void doAction();
	AddCop (int number, float x, float y, Simulation* s);
private:
	int number;
	float x;
	float y;

};

class AddCam : public Action {
public:
	bool IsActionPossible ();
	void doAction();
	AddCam (int number,float x, float y, Simulation* s);
private:
	int number;
	float x;
	float y;

};












#endif
