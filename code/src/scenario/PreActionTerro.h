/**
   @author: Remy, Adrien K.
 */
#ifndef PREACTIONTERRO_H
#define PREACTIONTERRO_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>

#include "Action.h"
#include "StuffList.h"
#include "simulation/npc.h"
#include "generation/tile.h"
#include "Actions.h"
#include "ScenarioActionList.h"
#include "NewMov.h"
#include "tile.h"
#include "position.h"
#include "npc.h"



void newMovement (NewMov n, LocalState* s);

bool isPlantable (Tile t) ;

float distance(LocalState* s, NPC* npc) ;


bool isInThePack(LocalState* s, int stuffID) ;



#endif
