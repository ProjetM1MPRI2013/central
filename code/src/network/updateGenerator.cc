#include <assert.h>

#include "updateGenerator.h"
#include "simulation/simulation.h"
#include "playerUpdate.h"

UpdateGenerator::UpdateGenerator(Simulation* globalState, Server* server) :
  globalState(globalState), server(server)
{
}


void UpdateGenerator::update(){
  for(int playerId : server->getConnectedPlayers())
    {
      GameUpdate update = generateUpdate(*globalState->getPlayerByID(playerId)) ;
      server->sendMessage<GameUpdate>(update, playerId, false) ;
    }
}

GameUpdate UpdateGenerator::generateUpdate(Player &player) {
  GameUpdate update ;
  PlayerUpdate p_update(player);
  update.setPlayerUpdate(p_update);
  std::pair<int,int> tilePos = player.getPosition()->isInTile() ;
  assert(tilePos.first >=0 && tilePos.first < globalState->getMap()->getMapWidth()) ;
  assert(tilePos.second >=0 && tilePos.second < globalState->getMap()->getMapWidth()) ;
  if(tilePos.first != globalState->getMap()->getMapWidth() -1)
    {
      //Add Right Tile
      addAllNpcs(update, globalState->getMap()->getTileRef(tilePos.first+1, tilePos.second));
    }
  if(tilePos.first != 0)
    {
      //Add Left Tile
      addAllNpcs(update, globalState->getMap()->getTileRef(tilePos.first-1, tilePos.second));
    }
  if(tilePos.second != globalState->getMap()->getMapHeight() -1)
    {
      //Add Up Tile
      addAllNpcs(update, globalState->getMap()->getTileRef(tilePos.first, tilePos.second+1));
    }
  if(tilePos.second != 0)
    {
      //Add Down Tile
      addAllNpcs(update, globalState->getMap()->getTileRef(tilePos.first, tilePos.second-1));
    }

  return update ;
}

void UpdateGenerator::addAllNpcs(GameUpdate &update, Tile &tile){
  std::list<NPC*> npcs = tile.getNPCs() ;
  for(NPC* npc : npcs)
    {
      update.addNpcUpdate(NpcUpdate(*npc));
    }
  return ;
}
