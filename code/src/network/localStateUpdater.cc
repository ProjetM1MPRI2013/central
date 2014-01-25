#include "localStateUpdater.h"
#include "simulation/simulation.h"

#include "debug.h"

LocalStateUpdater::LocalStateUpdater(Simulation* state, Client* client) :
  localState(state), client(client)
{
}


void LocalStateUpdater::update(sf::Time dt){
  std::vector<GameUpdate*> updates = client->receiveMessages<GameUpdate>() ;
  DBG << "Update : received " << updates.size() << "updates" ;
  if(!updates.empty())
    {
      GameUpdate * local_update = updates.back();
      applyPlayerUpdate(local_update->getPlayerUpdate()) ;
    }
  for(GameUpdate * l_update : updates)
      delete l_update ;
  return ;
}

void LocalStateUpdater::applyPlayerUpdate(PlayerUpdate &p_update){

  DBG << "Local Updater : updated position of player " << p_update.player_id ;
  Position * pos = localState->getPlayerByID(p_update.player_id).getPosition() ;
  if(pos->getX() < localState->getMap()->getMapWidth()
     && pos->getX() >= 0
     && pos->getY() < localState->getMap()->getMapHeight()
     && pos->getY() >= 0)
    {
      pos->setX(p_update.pos.getX());
      pos->setY(p_update.pos.getY());
    }
  else
    LOG(warning) << "Local Updater : position of player outside the map" ;
  return ;
}

void LocalStateUpdater::applyNpcUpdate(NpcUpdate &npc_update){

}
