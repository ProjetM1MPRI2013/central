#include "Stack.h"
#include "../hud/hudTerro.h"
#include <iostream>
#include <string>
#include <fstream>

Tile* getTile(Simulation* s) {
	std::cout << "getTile" << std::endl ;
	Player* p = s->getPlayer();
	std::cout << "getTile 1" << std::endl ;
	Position* pos = p->getPosition();
	 std::cout << pos->getX() << "," << pos->getY()  << std::endl ;
	std::cout << pos->getX() << std ::endl;
	std::cout << "getTile 2" << std::endl ;
	Geography* map = s->getMap();
	std::cout << "getTile 3" << std::endl ;
	std::cout << map->getMapHeight() << std::endl;
	std::cout << "getTile 3.2" << std::endl ;
	Tile t = pos->isInTile(*map);
	std::cout << "getTile 4" << std::endl ;
	return &(t
		/*s->getPlayer()->getPosition()->isInTile(
				*(s->getMap())
				)
				*/

		)
		;};

Stack::Stack (Simulation* s, PreHud* h){
  actionsName = Actions::NONE;
  basicStuff = 0;
  hud = h;
  sim = s;
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
Action* Stack::ActionOfStack(Actions a) {
  Stuff* b (this->getBasic());
   std::cout<< "nobody ActionOFSTACK" << std::endl ;

  Simulation* sim(this->getSim());
  std::cout << "nobody ActionOFSTACK.1" << std::endl ;
  switch (a)
    {
    case Actions::DROP :
    {
       	std::cout << "nobody ActionOFSTACK.2.0" << std::endl ;
    	return (Action *) new Drop(b,sim);
    };
    case Actions::ATTACK :
      {
	NPC* victim(this->getNpc());
	return ((Action *) new Attack((Weapon*)b,victim,sim));
      };
    case Actions::RELOAD :
      {
    	  std::cout << "nobody ActionOFSTACK.2.1" << std::endl ;
    	  Stuff* amu(this->getStuff());
    	  return ((Action *) new Reload ((Gun*)b,(Ammunition *)amu,sim));
      };
	case PLANT :
	{
		std::cout << "nobody ActionOFSTACK.2.2" << std::endl ;
		Tile* t = getTile(sim);
		std::cout << "nobody ActionOFSTACK.2.2.1" << std::endl ;
		return (Action *) new Plant ((Bomb *)b, t,sim);
	}
    default:
    	std::cout << "nobody ActionOFSTACK.2.3" << std::endl ;
      std::cerr << "Stack.cc : error in ActionOfState \n";
    };
  std::cout << "nobody ActionOFSTACK.2" << std::endl ;
  return new Action("lolol error", sim);
};

void Stack::sendAction () {
	std::cout << "nobody sendAction" << std::endl ;
	std::cout << "nobody sendAction.0" << std::endl ;
	if ((this->SoNList).empty())
	{   std::cout << this->actionsName << std::endl ;
	std::cout << "nobody sendAction.1" << std::endl ;
		Actions name = this->actionsName;
		std::cout << "nobody sendAction.0" << std::endl ;
		Action* a (this->ActionOfStack(name));
		std::cout << "nobody sendAction.1.1" << std::endl ;
		if (a->isActionPossible ())
		  {
			std::cout << "nobody sendAction.2" << std::endl ;
		    a->doAction();
		    std::cout << "nobody sendAction.3" << std::endl ;
		  }
		else
		  { std::cout << "nobody sendAction.2.1" << std::endl ;
			//(this->hud)->setwf(WF_NOTPOSSIBLE);
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
	      (this->hud)->setwf(WF_STUFF)
	      }
	    */
	};
};

void Stack::newAction(Actions a, Stuff* sf) {
	std::cout << "nobody newAction" << std::endl ;
  (SoNOfActions (a,(this->SoNList)));
  this->actionsName =a ;
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
		//(this->hud)->setwf(WF_ERROR);
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
		//(this->hud)->setwf(WF_ERROR);
		/*todo : envoyer message d'erreur*/
	};
};

