#ifndef STACK_H
#define STACK_H

enum SoN {STUFF,NPC};

class Stack {
 public :
	Stack (HudTerro h);
	void cancel ();
	void newAction (string sg, Stuff* sf);
	void sendNpc (Npc*);
	void sendStuff(Stuff*);
 private :
	HudTerro hud ;
	void sendAction ();
	std::string ActionName;
	Stuff* BasicStuff;
	std::list<SoN> SoNList;
	std::list<Npc*> NpcList;
	std::list<Stuff*> StuffList;
};

#endif
