#include "localStateUpdater.h"
#include "simulation/localState.h"

LocalStateUpdater::LocalStateUpdater(LocalState* state, Client* client) :
  localState(state), client(client)
{
}


void LocalStateUpdater::update(){
  std::vector<GameUpdate*> updates = client->receiveMessages<GameUpdate>() ;
  if(!updates.empty())
    {
      GameUpdate * local_update = updates.back();
      applyPlayerUpdate(local_update->getPlayerUpdate()) ;
    }
  for(GameUpdate * l_update : updates)
    {
      delete l_update ;
    }
  return ;
}

void LocalStateUpdater::applyPlayerUpdate(PlayerUpdate &p_update){
  localState->getOwnerLocalState().getPosition()->setX(p_update.pos.getX());
  localState->getOwnerLocalState().getPosition()->setY(p_update.pos.getY());
  return ;
}
