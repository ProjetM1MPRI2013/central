#ifndef STACK_H
#define STACK_H

enum SoN {STUFF,NPC};

class Stack {
 public :
	Stack ();
	void cancel ();
	void newAction (string sg, Stuff* sf);
	void sendNpc (Npc*);
	void sendStuff(Stuff*);
	void setHud (HudTerro* h);
	void setSim (simulation* s);
	Npc* getNpc ();
	Stuff getStuff () ;
	Stuff* getBasic();
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
