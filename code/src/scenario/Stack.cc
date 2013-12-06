#include "Stack.h"
#include "../hud/hudTerro.h"
/*todo*/

Tile* getTile(Simulation* s) {return 0;};

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


NPC* Stack::getNpc() {
	NPC* n((this->NpcList).front());
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
	this->actionsName = Actions::NONE;
};

std::list<SoN> SoNOfActions (Actions a) {
  switch (a)
    {
    case DROP :
      return std::list<SoN> ();
    case ATTACK :
      return (std::list<SoN> (1,SON_NPC));
    case RELOAD :
      return (std::list<SoN> (1,SON_STUFF));
    case PLANT :
      return std::list<SoN> ();
    default:
      std::cerr << "Stack.cc : error in SoNOfActions \n";
      break;
    };
  return std::list<SoN> ();
};

Action* Stack::ActionOfStack(Actions a) {
  Stuff* b (this->getBasic());
  Simulation* sim(this->getSim());
  switch (a)
    {
    case Actions::DROP :
      return (Action *) new Drop(b,sim);
    case Actions::ATTACK :
      {
	NPC* victim(this->getNpc());
	return (Action *) new Attack((Weapon*)b,victim,sim);
      };
    case Actions::RELOAD :
      {
      Stuff* amu(this->getStuff());
      return (Action *) new Reload ((Gun*)b,(Ammunition *)amu,sim);
      };
	case PLANT :
	{
	  return (Action *) new Plant ((Bomb *)b, getTile(sim),sim);
	}
    default:
      std::cerr << "Stack.cc : error in ActionOfState \n";
    };
  return new Action("lolol error", sim);
};

void Stack::sendAction () {
	if ((this->SoNList).empty())
	{
		Action* a (this->ActionOfStack(this->actionsName));
		if (a->isActionPossible ())
		  {
		    a->doAction();
		  }
		else
		  {
		    /*todo envoyer un message d'erreur*/
		  };
		this->cancel();
		(this->hud)->setwf(WF_NONE);
	}
	else
	  { if ((this->SoNList).front() == SON_NPC)
	      {
		(this->hud)->setwf(WF_CLICK);
	      };
	    /*
	      else
	      {
	      (this->hud).setwf(ITEM)
	      }
	    */
	};
};

void Stack::newAction(Actions a, Stuff* sf) {
  this->SoNList = (SoNOfActions (a));
  this->basicStuff = sf;
  this->sendAction();
};

void Stack::sendNpc(NPC* n) {
	if ((this->SoNList).front() == SON_NPC)
	{
		(this->NpcList).push_front(n);
		(this->SoNList).pop_front();
		this->sendAction();
	}
	else
	{
		/*todo : envoyer message d'erreur*/
	};
};
void Stack::sendStuff(Stuff* s) {
	if ((this->SoNList).front() == SON_STUFF)
	{
		(this->StuffList).push_front(s);
		(this->SoNList).pop_front();
		this->sendAction();
	}
	else
	{
		/*todo : envoyer message d'erreur*/
	};
};

