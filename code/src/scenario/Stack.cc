#include "Stack.h"

Stack::Stack (){
  actionsName = Actions::NONE;
};

void Stack::setHud(HudTerro* h ) {
	this->hud = h;
};

Stuff* Stack::getBasic() {
	return this->basicStuff;
};

Simulation* Stack::getSim() {
	return this->sim;
};

Stuff* Stack::getStuff() {
	Stuff* s((this->StuffList).front());
	(this->StuffList).pop_front();
	return s;
};


NPC* Stack::getNpc()) {
	Npc* n((this->NpcList).front());
	(this->NpcList).pop_front();
	return n;
};

Actions Stack::getActionsName() {
	return (this->actionsName);
};

void Stack::setActionsName(Actions a) {
	(this->actionsName)= a;
};

void Stack::cancel () {
	this->SoNList.clear ();
	this->NpcList.clear ();
	this->StuffList.clear ();
	this->basicStuff = 0;
	this->ActionName = NONE;
};

std::list<SoN> SoNOfActions (Actions a) {
	switch (a)
	{
		case DROP :
			return std::list<SoN>;
		break;
		case ATTACK :
			return (std::list<SoN> (1,SON_NPC));
		break;
		case RELOAD :
			return (std::list<SoN> (1,SON_STUFF));
		break;
		case PLANT :
			return std::list<SoN>;
		break;
	};
};

Action ActionOfState(Stack* s, Actions a) {
  Stuff* b(s->getBasic());
	Simulation* sim(s->getSim());
	switch (a)
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
};

void Stack::sendAction () {
	if ((this->SoNList).empty())
	{
		Action a(ActionOfStack(this,this->ActionName));
		if (a.isActionPossible ())
		{
			a.doAction();
		}
		else
		{
			/*todo envoyer un message d'erreur*/
		};
		this.cancel();
		(this->hud)->setwf(CLICK) = NONE;
	};
	else
	{ if ((this->SoNList).front()= SON_NPC)
		{
			(this->hud).setwf(CLICK)
		}
		else
		{
			(this->hud).setwf(ITEM)
		}
	};
};

void Stack::newAction(Actions a, Stuff* sf) {
	this->SoNList = (SoNOfActions a);
	this->basicStuff-> sf;
	this->sendAction();
};

void SendNpc(Npc* n) {
	if ((this->SoNList).front() = SON_NPC)
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
void SendStuff(Stuff* s) {
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

