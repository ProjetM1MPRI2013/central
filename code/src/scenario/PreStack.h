/**
   @author: Remy
 */

#include "StuffList.h"
#include "Action.h"
#include "ActionsTerro.h"

#ifndef PRESTACK_H
#define PRESTACK_H


std::string stringOfActions(ActionType a) ;
std::list<SoN> SoNOfActions(ActionType a);
Action* createAction(ActionType a,int basicStuff, std::list<boost::uuids::uuid> npcList, std::list<int> stuffList,LocalState* sim) ;

#endif
