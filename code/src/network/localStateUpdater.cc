#include <cmath>

#include "localStateUpdater.h"
#include "simulation/localState.h"

#include "debug.h"

/*
 * @author mheinric
 */

using namespace std ;


LocalStateUpdater::LocalStateUpdater(LocalState* state, Client* client) :
  localState(state), client(client), lastUpdate(sf::Time::Zero), diffPos()
{
}


void LocalStateUpdater::update(sf::Time dt){
  vector<GameUpdate*> updates = client->receiveMessages<GameUpdate>() ;
  DBG << "Update : received " << updates.size() << "updates" ;
  if(!updates.empty())
    {
      GameUpdate * local_update = updates.back();
      applyPlayerUpdate(local_update->getPlayerUpdate(), dt) ;
    }
  lastUpdate += dt ;
  for(GameUpdate * l_update : updates)
      delete l_update ;

  updatePlayerPosition(dt) ;

  return ;
}

void LocalStateUpdater::applyPlayerUpdate(PlayerUpdate &p_update, sf::Time dt){

  DBG << "Local Updater : updated position of player " << p_update.player_id ;
  Player& player = localState->getOwner() ;
  if(player.getID() != p_update.player_id)
    {
      LOG(warning) << "Local Updater : The received update does not concern the local Player" ;
      return ;
    }

  Position pos = player.getPosition() ;
  if(pos.getX() < localState->getMap()->getMapWidth()
     && pos.getX() >= 0
     && pos.getY() < localState->getMap()->getMapHeight()
     && pos.getY() >= 0)
    {
      diffPos.setX(p_update.pos.getX() - pos.getX());
      diffPos.setY(p_update.pos.getY() - pos.getY());

      if(diffPos.distance(Position()) > 5)
        {
          //Great distance between server and Local -> teleport
          player.setPosition(p_update.pos);
        }

    }
  else
    LOG(warning) << "Local Updater : position of player outside the map" ;
  return ;
}

void LocalStateUpdater::applyNpcUpdate(NpcUpdate &npc_update){
}

void LocalStateUpdater::updatePlayerPosition(sf::Time dt) {
  //Parametre de l'exponentielle decroissante
  float param = 5. ;
  float ponderation = param * exp(- param * lastUpdate.asMilliseconds()) * dt.asMilliseconds() ;
  Position pos = localState->getOwner().getPosition();
  //min and max to avoid getting outside the map
  float posX = pos.getX() + ponderation * diffPos.getX() ;
  posX = max(posX,(float) 0) ;
  posX = min(posX,(float) localState->getMap()->getMapWidth()) ;
  float posY = pos.getY() + ponderation * diffPos.getY() ;
  posY = max(posY,(float) 0) ;
  posY = min(posY,(float) localState->getMap()->getMapHeight()) ;

  pos.setX(posX);
  pos.setY(posY);
  localState->getOwner().setPosition(pos);

}
