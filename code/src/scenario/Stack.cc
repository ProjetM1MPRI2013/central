#include "Stack.h"
#include "Action.cc"
#include "hudTerro.cc"

Stack::Stack (HudTerro h){
	this->hud = h ;
};

Stack::clear () {
	this->SoNList.clear ();
	this->NpcList.clear ();
	this->StuffList.clear ();
	this->BasicStuff = 0;
	this->ActioName = "";
};
void Stack::SendAction () {
	if ((this->SoNList).empty())
	{
		Action a(ActionOfStack(this,this->ActionName));
		if (a.isActionPossible ())
		{
			a.doAction()
		}
		else
		{
			/*todo envoyer un message d'erreur*/
		};
		this.clear();
		(this->hud).setwf(CLICK) = NONE;
	};
	else
	{ if ((this->SoNList).front()= NPC)
		{
			(this->hud).setwf(CLICK)
		}
		else
		{
			(this->hud).setwf(ITEM)
		}
	};
};

void Stack::newAction(string sg, Stuff* sf) {
	this->SoNList = SoNOfString sg;
	this->BasicStuff-> sf;
	this->sendAction();
};

void SendNpc(Npc*) {
	if ((this->SoNList).front() = NPC)
	{
		(this->NpcList).push_front(Npc*);
		(this->SoNList).pop_front();
		this->sendAction;
	}
	else
	{
		/*todo : envoyer message d'erreur*/
	};
};
void SendStuff(Stuff*) {
	if ((this->SoNList).front() = Stuff)
	{
		(this->StuffList).push_front(Stuff*);
		(this->SoNList).pop_front();
		this->sendAction;
	}
	else
	{
		/*todo : envoyer message d'erreur*/
	};
};
