/**
   @author: Remy
 */

#include "PreActionTerro.h"
#include "ActionsTerro.h"
#include <iostream>
#include <list>

#include "localState.h"
#include "globalState.h"

#include "network/client.h"
#define DEBUG false
#include "debug.h"

bool isPlantable (Tile* t) {
	switch(t->getType())
	// todo choisir les quelles sont plantables
	{case(ROADH) : return true;
	case(ROADV) : return true;
	case(INTER) : return true;
	case(BANK) : return true;
	case(HOUSE): return true;
	case(BLANK): return true;
	default: return true;
	};
	return false;
};

float distance(LocalState* s, NPC* npc) {
	return s->getOwner().getPosition().distance(npc->getPosition());
};




bool isInThePack(LocalState* s, int stuffID) {
	return s->getOwner().hasItemByID(stuffID);
};


void newMovement (NewMov n, LocalState* s){
  DBG << "Client : New Movement begin";
	NewMovNetwork newMovNet(n,s->getOwner().getID(),s);
  DBG << "Client : New Movement from player : " << s->getOwner().getID() << " " << stringNewMov(n);
	s->getOwner().setDirection(newMovNet.newDirection);
	s->getClient()->sendMessage(newMovNet,true);
};

void newMouseMovement(Position pos, LocalState* s) {
  DBG << "Client : New MouseMovement begin";
  NewMouseMovNetwork newMouseMovNet(pos,s->getOwner().getID());
	DBG << "Client : New MouseMovement from player : " << s->getOwner().getID() << " " << pos;
	s->getOwner().setDestination(pos);
  s->getClient()->sendMessage(newMouseMovNet,true);
};

