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
Action* createAction(ActionType a,int basicStuff, std::list<boost::uuids::uuid> npcList, std::list<int> stuffList,LocalState* sim) ;

#endif
