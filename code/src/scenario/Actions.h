#ifndef ACTIONS_H
#define ACTIONS_H

#include<list>
#include<string>

enum Actions {DROP,ATTACK,PLANT,RELOAD,NONE};

enum SoN {
	SON_STUFF, SON_NPC
};

void SoNOfActions(Actions a,std::list<SoN> l);

std::string stringOfActions(Actions a) ;

#endif
