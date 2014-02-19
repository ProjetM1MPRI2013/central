/**
   @author: Adrien K.
 */


#ifndef PRESCENARIOACTIONLIST_H
#define PRESCENARIOACTIONLIST_H

#include "simulation/npc.h"
#include "generation/tile.h"
#include "ScenarioAction.h"
#include "scenario/ActionsTerro.h"
#include "NewMov.h"
#include <iostream>
#include <cerrno>


class Couple {
public:
	int x;
	int y;
	Couple (int x, int y);
};

Couple* directionToInt(Direction a);
Couple* newMovToInt(NewMov a);
Direction intToDirection(Couple* a);

/**
 * @brief The player changes of direction.
 */
class ChangeDirection: public ScenarioAction {
public:
	int playerID;

	/**
	 * @brief The new direction of the player
	 */
	Direction newDirection;
	int timeStamp;

	ChangeDirection(int id, Direction direction, int ts, Simulation* s);
	ChangeDirection(const ChangeDirection&);

	virtual void run();

	//AbstractMessage functions
	virtual AbstractMessage* copy();
protected :
	//Serialization
	ChangeDirection() {}

	SIMPLE_MESSAGE(ChangeDirection, ScenarioAction, playerID, newDirection, timeStamp)

};

/**
 * @brief The player changes destination.
 */
class ChangeDestination: public ScenarioAction {
public:
	int playerID;

	/**
	 * @brief The new destination of the player
	 */
	Position destination;
	int timeStamp;

	ChangeDestination(int id, Position destination, int ts, Simulation* s);
	ChangeDestination(const ChangeDestination&);

	virtual void run();

	//AbstractMessage functions
	virtual AbstractMessage* copy();
protected :
	//Serialization
	ChangeDestination() {}

	SIMPLE_MESSAGE(ChangeDestination, ScenarioAction, playerID, destination, timeStamp)

};

class AddCops: public ScenarioAction {
public:
	int number;
	float x;
	float y;
	AddCops (int n, float xx, float yy,Simulation* s);
	AddCops (const AddCops&);

	virtual void run ();

	//AbstractMessage functions
	virtual AbstractMessage* copy();

protected :
	//Serialization
	AddCops(){}

	SIMPLE_MESSAGE(AddCops, ScenarioAction, number, x, y)
};


class AddCams: public ScenarioAction {
public:
	int number;
	float x;
	float y;
	AddCams(int number,float x,float y,Simulation* s);
	AddCams(const AddCams&);

	virtual void run ();

	virtual AbstractMessage* copy();

private :
	//Serialization
	AddCams(){}

	SIMPLE_MESSAGE(AddCams, ScenarioAction, number, x, y)
};


/*********************************************************
** Library for created scenario action**
*********************************************************/

void DropItem (int stuffID, int playerID, Simulation* simulation);
void Explosion (int p,std::pair<int,int>,Simulation* s);
void KillNPC(boost::uuids::uuid target, Simulation* s );


#endif
