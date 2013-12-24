#ifndef STACK_H
#define STACK_H
#include <cerrno>
#include <iostream>
#include "Actions.h"
#include "preHud.h"
#include "simulation/simulation.h"
#include "scenario/ActionsTerro.h"
#include "tile.h"
#include "ActionCreator.h"

Tile* getTyle(Simulation* s);


Action* create (Actions a,Stuff* b,std::list<NPC*> npcs,std::list<Stuff*> stuffs,Simulation* sim);



/**
 * @brief The object Stack will stack informations needed to create an action and send it when he can
 */
class Stack {
public:
	/**
	 * @brief Create a Stack
	 */
	Stack(Simulation* s,PreHud* h );
	/**
	 *@brief Cancel an action which was waiting to be send
	 */
	void cancel();
	/**
	 * @brief Create a begining of an action
	 * @param a A name of an action
	 * @param sf The basic stuff (the player clicked on it to do the action)
	 */
	void newAction(Actions a, Stuff* sf);
	/**
	 * @brief Used when the player click on a Npc
	 * @param n The Npc
	 */
	void sendNpc(NPC* n);
	/**
	 * @brief Used when the player click on a Stuff
	 * @param s The stuff.
	 */
	void sendStuff(Stuff* s);
	Action* ActionOfStack(Actions a);

private:
	/**
	 * @brief if the Action is completed, look if it possible and do the action,
	 * else ask to the hub an NPC or a Stuff.
	 */
	void sendAction();
	Stuff* getStuff();
	NPC* getNpc ();
	Simulation* sim;
	PreHud* hud;
	Actions actionsName;
	Stuff* basicStuff;
	std::list<SoN> SoNList;
	std::list<NPC*> NpcList;
	std::list<Stuff*> StuffList;
};



#endif
