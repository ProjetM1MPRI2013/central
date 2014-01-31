#include "gameUpdate.h"
#include <boost/serialization/export.hpp>

/*
 * @author mheinric
 */

GameUpdate::GameUpdate() : p_update(), npc_updates(){}

GameUpdate::~GameUpdate(){}

void GameUpdate::setPlayerUpdate(const PlayerUpdate &playerUpdate) {
  p_update = playerUpdate ;
}

void GameUpdate::addNpcUpdate(const NpcUpdate &npcUpdate) {
  npc_updates.push_back(npcUpdate);
  return ;
}

PlayerUpdate& GameUpdate::getPlayerUpdate(){
  return p_update ;
}


GameUpdate * GameUpdate::copy(){
  GameUpdate * update = new GameUpdate() ;
  update->setPlayerUpdate(this->getPlayerUpdate());
  for(NpcUpdate npc_update : this->npc_updates)
    {
      update->addNpcUpdate(npc_update);
    }
  return update ;
}
