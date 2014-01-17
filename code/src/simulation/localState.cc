#include "localState.h"

LocalState::LocalState(std::string _seed, const Player& _player) : Simulation(_seed, std::vector<Player*>()),
  owner_player(_player){
  addPlayer(&owner_player);
  local_map = (Geography*) new Generation1(_seed);
}

sf::Time &LocalState::getLocalTime(){
  return localtime;
}

/**
 * @brief LocalState::getRelativePlayerTile
 * @param x : number of tiles to the right from the players position
 * @param y : number of tiles to the top from the players position
 * @return a reference to a Tile if on map, or owner's tile otherwise
 */
Tile& LocalState::getRelativePlayerTile(int x, int y){
  int absciss = owner_player.getPosition()->isInTile(*local_map).getCoord().getAbs();
  int ordinate = owner_player.getPosition()->isInTile(*local_map).getCoord().getOrd();
  absciss += x;
  ordinate += y;
  if ((absciss < local_map->getMapWidth()) && (absciss >= 0)
       && (ordinate < local_map->getMapHeight()) && (ordinate >= 0)){
      return local_map->getTileRef(absciss, ordinate);
    }
  //TODO {Denys} : think about returning meaning
  else {
      return owner_player.getPosition()->isInTile(*local_map);
    }
}

/**
 * @brief LocalState::getPlayerLocalState
 * @return  reference to the owner
 */
Player& LocalState::getOwnerLocalState(){
  return owner_player;
}

Tile& LocalState::getTile(Position p, Layers l){
  return p.isInTile(*local_map);
}

void LocalState::update(){
  owner_player.updatePosition(localtime);
  //for each loop
  for (NPC &npc: npc_list) {
      npc.updatePosition(localtime, *local_map);
    }
}

Geography& LocalState::getLocalMap(){
  return *local_map;
}
