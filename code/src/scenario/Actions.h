/**
   @author: Remy
 */


#ifndef ACTIONS_H
#define ACTIONS_H

#include<list>
#include<string>


enum SoN {
	SON_STUFF, SON_NPC
};

class ActionType {
public:
	ActionType (std::string s,std::list<SoN> l);
	std::string name;
	std::list<SoN> SoNlist;
};

/*
enum Actions {DROP,ATTACK,PLANT,RELOAD,NONE};


void SoNOfActions(Actions a,std::list<SoN> l);

std::string stringOfActions(Actions a) ;
*/
#endif
