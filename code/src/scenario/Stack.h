#ifndef STACK_H
#define STACK_H

enum SoN {STUFF,NPC};
class Action {};
class Stuff {};
class Npc {};
class HudTerro {};
class Simulation {};

#include "Action.h"
#include "../hud/hudTerro.h
/**
   * @brief The object Stack will stack informations needed to create an action and send it when he can
  */
class Stack {
 public :
	/**
	   * @brief Create a Stack
	*/
	Stack ();
	/**
	   * @brief Cancel an action which was waiting to be send
	*/
	void cancel ();
	/**
	   * @brief Create a begining of an action
	   * @param a A name of an action
	   * @param sf The basic stuff (the player clicked on it to do the action)
	*/
	void newAction (Actions* a, Stuff* sf);
	/**
	   * @brief Used when the player click on a Npc
	   * @param n The Npc
	*/
	void sendNpc (Npc* n);
	/**
	   * @brief Used when the player click on a Stuff
	   * @param s The stuff.
	*/
	void sendStuff(Stuff* s);
	/**
		   * @brief Used to join the hud to the stack
		   * @param h the hud
	*/
	void setHud (HudTerro* h);
	/**
		   * @brief Used to join the simulation to the stack
		   * @param s the simulation
	*/
	void setSim (Simulation* s);
	/**
	 *@brief get the first Npc of the list
	*/
	Npc* getNpc ();
	/**
	 *@brief get the first Stuff of the list
	*/
	Stuff getStuff () ;
	/**
	 * @brief get the basic stuff
	*/
	Stuff* getBasic();
	/**
	   * @brief get the simulation
	*/
	Simulation* getSim();
 private :
	Simulation* sim;
	HudTerro* hud ;
	void sendAction ();
	std::string ActionName;
	Stuff* BasicStuff;
	std::list<SoN> SoNList;
	std::list<Npc*> NpcList;
	std::list<Stuff*> StuffList;
};

std::list<SoN> SoNOfActions (Actions* a);

Action ActionOfState(Stack* s, Actions* a);


#endif
