#include <assert.h>

#include "debug.h"
#include "updateGenerator.h"
#include "simulation/globalState.h"
#include "playerUpdate.h"

/*
 * @author mheinric
 */

UpdateGenerator::UpdateGenerator(GlobalState *globalState, Server* server) :
  globalState(globalState), server(server), last_sent()
{
}


void UpdateGenerator::update(sf::Time dt){
  last_sent += dt ;
  if(last_sent.asMilliseconds() > 1000.)
    {
      DBG << "Update Generator : sending update" ;
      last_sent = sf::Time::Zero ;
      for(int playerId : server->getConnectedPlayers())
        {
          GameUpdate update = generateUpdate(globalState->getPlayerByID(playerId)) ;
          server->sendMessage<GameUpdate>(update, playerId, false) ;
        }
    }
}

GameUpdate UpdateGenerator::generateUpdate(Player& player) {
  DBG << "Generates an update for Player " << player.getID() ;
  GameUpdate update ;
  PlayerUpdate p_update(player);
  update.setPlayerUpdate(p_update);
  std::pair<int,int> tilePos = player.getPosition().isInTile() ;
  if(!(tilePos.first >=0 && tilePos.first < globalState->getMap()->getMapWidth()))
    DBG << "Player Outside the map" ;
  if(!(tilePos.second >=0 && tilePos.second < globalState->getMap()->getMapWidth()))
    DBG << "Player Outside the map" ;

  for(int i = 0 ; i <  globalState->getMap()->getMapWidth() ; i++ )
    {
      for(int j = 0 ; j <  globalState->getMap()->getMapHeight() ; j++ )
        addAllNpcs(update, globalState->getMap()->getTileRef(i,j));
    }

  return update ;
}

void UpdateGenerator::addAllNpcs(GameUpdate &update, Tile &tile){
  std::list<NPC*> npcs = tile.getNPCs() ;
  for(NPC* npc : npcs)
      update.addNpcUpdate(NpcUpdate(*npc));
  return ;
}
