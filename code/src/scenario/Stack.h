#ifndef STACK_H
#define STACK_H
#include <cerrno>
#include <iostream>
#include "Actions.h"
#include "preHud.h"
#include "simulation/simulation.h"
#include "scenario/ActionsTerro.h"


Tile* getTyle(Simulation* s);

/**
 * @brief The object Stack will stack informations needed to create an action and send it when he can
 */
class Stack {
public:
	/**
	 * @brief Create a Stack
	 */
	Stack();
	/**
	 *@brief Cancel an action which was waiting to be send
	 */
	void cancel();
	/**
	 *@brief Give the name of the Action
	 */
	Actions getActionsName();
	void setActionsName(Actions a);
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
	/**
	 * @brief Used to join the hud to the stack
	 * @param h the hud
	 */
	void setHud(PreHud* h);
	/**
	 * @brief Used to join the simulation to the stack
	 * @param s the simulation
	 */
	void setSim(Simulation* s);
	/**
	 *@brief get the first Npc of the list
	 */
	NPC* getNpc();
	/**
	 *@brief get the first Stuff of the list
	 */
	Stuff* getStuff();
	/**
	 * @brief get the basic stuff
	 */
	Stuff* getBasic();
	/**
	 * @brief get the simulation
	 */
	Simulation* getSim();
	Action* ActionOfStack(Actions a);

private:
	/**
	 * @brief if the Action is completed, look if it possible and do the action,
	 * else ask to the hub an NPC or a Stuff.
	 */
	void sendAction();

	Simulation* sim;
	PreHud* hud;
	Actions actionsName;
	Stuff* basicStuff;
	std::list<SoN> SoNList;
	std::list<NPC*> NpcList;
	std::list<Stuff*> StuffList;
};



#endif
