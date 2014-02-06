#include "Stack.h"
#include "localState.h"
#include "../hud/hudTerro.h"
#include <iostream>
#include <string>
#include <fstream>
//#include "ActionCreator.h"
#define DEBUG false
#define LOG false

Tile getTile(LocalState* s) {
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


/* generated code*/

void SoNOfActions(ActionType a,std::list<SoN> l){
	switch (a) {
	case ToA_Attack:{l.push_front(SON_NPC);

	} break;
	case ToA_Reload:{l.push_front(SON_STUFF);

	} break;
	case ToA_Plant:{l.push_front(SON_STUFF);

	} break;
	case ToA_Drop:{
	} break;
	//Should not happens
	};
};
Action* createAction(ActionType a,int basicStuff, std::list<int> npcList, std::list<int> stuffList,LocalState* sim) {
	switch (a) {
	case ToA_Attack:{
		int weapon = basicStuff;
		int victim= npcList.back();
		npcList.pop_back();
		return (new A_Attack (weapon, victim, sim));
	};
	case ToA_Reload:{
		int gun = basicStuff;
		int ammunition= stuffList.back();
		stuffList.pop_back();
		return (new A_Reload (gun, ammunition, sim));
	};
	case ToA_Plant:{
		int bomb = basicStuff;
		int zone= stuffList.back();
		stuffList.pop_back();
		return (new A_Plant (bomb, zone, sim));
	};
	case ToA_Drop:{
		int stuff = basicStuff;
		return (new A_Drop (stuff, sim));
	};
	//Should not happens
	};
};

/*end of the generated code*/

Stack::Stack (LocalState* s, PreHud* h){
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
	this->cancel();
	SoNOfActions(a,this->SoNList);
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

