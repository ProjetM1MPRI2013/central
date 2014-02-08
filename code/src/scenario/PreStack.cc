#include "PreStack.h"


/*********************************************************
 ** Generated code**
 *********************************************************/
std::string stringOfActions(ActionType a) {
	switch (a) {
	case ToA_Attack:{
		return "Attack";}
	case ToA_Reload:{
		return "Reload";}
	case ToA_Plant:{
		return "Plant";}
	case ToA_Drop:{
		return "Drop";}
	//Should not happens
	};
};
void SoNOfActions(ActionType a,std::list<SoN> l){
	switch (a) {
	case ToA_Attack:{l.push_front(SON_NPC);

	}; break;
	case ToA_Reload:{l.push_front(SON_STUFF);

	}; break;
	case ToA_Plant:{
	}; break;
	case ToA_Drop:{
	}; break;
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
		std::pair<int,int> zone = sim->getCurrentTile();
		return (new A_Plant (bomb, zone, sim));
	};
	case ToA_Drop:{
		int stuff = basicStuff;
		return (new A_Drop (stuff, sim));
	};
	//Should not happens
	};
};
