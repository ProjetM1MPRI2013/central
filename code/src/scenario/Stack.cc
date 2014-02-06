#include "Stack.h"
#include "../hud/hudTerro.h"
#include <iostream>
#include <string>
#include <fstream>
//#include "ActionCreator.h"
#define DEBUG false
#define LOG false

// découper ici
Tile getTile(Simulation* s) {
	Player* p = s->getPlayer();
	Position& pos = p->getPosition();
	Geography* map = s->getMap();
	Tile& t = pos.isInTile(*map);
	return t;
;};

// Deprecated. Update it to not use pointers
// if you uncomment it.
//Stuff* getStuff(std::list<Stuff*> l) {
	//Stuff* s = l.front();
	//l.pop_front();
	//return s;
//};


Stack::Stack (Simulation* s, PreHud* h){
  actionType = 	ToA_Attack ; //TODO NOBODY
  stuffID = -1; // -1 must be an invalid stuff id.
  hud = h;
  sim = s;
};


void Stack::cancel () {
	this->SoNList.clear ();
	this->NpcList.clear ();
	this->StuffList.clear ();
	this->stuffID = -1;
	//this->actionsName = Actions::NONE;
};

Action* createAction (ActionType a, int stuffID,std::list<int> NpcList,std::list<int>StuffList,Simulation* sim) {
	return ((Action*) (new A_Drop(stuffID, sim))); //TODO NOBODY
};

Action* Stack::ActionOfStack(ActionType a) {
	return createAction (a,this->stuffID,this->NpcList,this->StuffList,this->sim);
  };

void Stack::sendAction () {
	if ((this->SoNList).empty()){
	//{   if (DEBUG) {std::cout << this->actionsName << std::endl ;};
		//Actions name = this->actionsName;
		Action* a (this->ActionOfStack(this->actionType));
		if (a->isActionPossible ())
		  {
		    a->doAction();
		  }
		else
		  { };
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

void Stack::newAction(ActionType a, int stuffID) {
  //this->SoNList = a; TODO SONOF ...
  this->actionType =a ;
  this->stuffID = stuffID;
  this->sendAction();
};

void Stack::sendNpc(int n) {
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
void Stack::sendStuff(int stuffID) {
	if ((this->SoNList).front() == SON_STUFF)
	{
		(this->StuffList).push_front(stuffID);
		(this->SoNList).pop_front();
		this->sendAction();
	}
	else
	{
		//(this->hud)->setwf(WF_ERROR);
		/*todo : envoyer message d'erreur*/
	};
};

