
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#include "PreStack.h"
std::string stringOfActions(ActionType a) {
switch (a) {
case ToA_Pick:{
return "Pick";}
case ToA_Kick:{
return "Kick";}
case ToA_Shoot:{
return "Shoot";}
case ToA_Reload:{
return "Reload";}
case ToA_Plant:{
return "Plant";}
case ToA_Drop:{
return "Drop";}
default: 
 //Should not happens 
 return "should not happen in stringofaction"; 
  }; 
 };
std::list<SoN> SoNOfActions(ActionType a){
	std::list<SoN> l;
switch (a) {
case ToA_Pick:{
}; break;
case ToA_Kick:{l.push_front(SON_NPC);

}; break;
case ToA_Shoot:{l.push_front(SON_NPC);

}; break;
case ToA_Reload:{l.push_front(SON_STUFF);

}; break;
case ToA_Plant:{
}; break;
case ToA_Drop:{
}; break;
default:  
	//Should not happens 
	break; 
  }; 
 return l; 
 };
Action* createAction(ActionType a,int basicStuff, std::list<boost::uuids::uuid> npcList, std::list<int> stuffList,LocalState* sim) {
switch (a) {
case ToA_Pick:{
int fake = basicStuff;
std::pair<int,int> zone= sim->getCurrentTile();
return (new A_Pick (fake, zone, sim));
};
case ToA_Kick:{
int weapon = basicStuff;
boost::uuids::uuid victim= npcList.back();
npcList.pop_back();
return (new A_Kick (weapon, victim, sim));
};
case ToA_Shoot:{
int gun = basicStuff;
boost::uuids::uuid victim= npcList.back();
npcList.pop_back();
return (new A_Shoot (gun, victim, sim));
};
case ToA_Reload:{
int gun = basicStuff;
int ammunition= stuffList.back();
stuffList.pop_back();
return (new A_Reload (gun, ammunition, sim));
};
case ToA_Plant:{
int bomb = basicStuff;
std::pair<int,int> zone= sim->getCurrentTile();
return (new A_Plant (bomb, zone, sim));
};
case ToA_Drop:{
int stuff = basicStuff;
std::pair<int,int> zone= sim->getCurrentTile();
return (new A_Drop (stuff, zone, sim));
};
default:
	//Should not happens
	return (new Action("fake", sim));
	break;
   }; 
 };
