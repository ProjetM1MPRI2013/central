/**
   @author: Remy
 */

#include "StuffList.h"
#include "Action.h"
#include "ActionsTerro.h"

#ifndef PRESTACK_H
#define PRESTACK_H


std::string stringOfActions(ActionType a) ;
void SoNOfActions(ActionType a,std::list<SoN> l);
Action* createAction(ActionType a,int basicStuff, std::list<int> npcList, std::list<int> stuffList,LocalState* sim) ;

#endif
