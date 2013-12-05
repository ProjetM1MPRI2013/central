#include "Stack.h"
#include "Action.cc"
#include "../hud/hudTerro.cc"


Stack::Stack (){
};

void Stack::setHud(HudTerro* h ) {
	this->hud = h;
};

Stuff* Stack::getBasic() {
	return this->BasicStuff;
};

Stuff* Stack::getSimulation() {
	return this->getSim();
};

Stuff* Stack::getStuff() {
	return (this->StuffList).front();
};


Npc* Stack::getNpc()) {
	return (this->NpcList).front();
};


void Stack::clear () {
	this->SoNList.clear ();
	this->NpcList.clear ();
	this->StuffList.clear ();
	this->BasicStuff = 0;
	this->ActioName = "";
};

std::list<SoN> SoNOfActions (Actions* a) {
	switch (*a)
	{
		case DROP :
			return std::list<SoN>;
		break;
		case ATTACK :
			return (std::list<SoN> (1,NPC));
		break;
		case RELOAD :
			return (std::list<SoN> (1,STUFF));
		break;
		case PLANT :
			return std::list<SoN>;
		break;
	};
};

Action ActionOfState(Stack* s, Actions* a) {
	Stuff* b(s->BasicStuff());
	Simulation* sim(s->getSim());
	switch (*a)
		{
			case DROP :
				return Drop::Drop(b,sim);
			break;
			case ATTACK :
				Npc* victim((s->NpcList).front());
				return Attack::Attack((Weapon*)b,victim,sim);
			break;
			case RELOAD :
				Ammunition* amu((s->StuffList).front());
				return Reload::Reload ((Gun*)b,amu,sim);
			break;
			case PLANT :
				return Plant::Plant (b,/*todo trouver la zone*/);
			break;
		};
}
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
		(this->hud)->setwf(CLICK) = NONE;
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

