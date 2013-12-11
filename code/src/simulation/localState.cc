#include "localState.h"

LocalState::LocalState(Player& _player, std::string _seed):
  owner_player(_player){
  local_map = new Geography(_seed);
  //view_range = _player->getViewRange();
  view_range = 10;

  /*initialization of the local_viewed*/
//  potential_viewed = new Tile** [2*view_range+1];
//  for (int i = 0; i < 2*view_range+1; ++i)
//     potential_viewed[i] = new Tile* [2*view_range+1];
//  rebuildLocalMap();
}

float LocalState::getLocalTime(){
  return localtime_ms;
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
  //TODO {denys} : remove this fake timer
  localtime_ms +=1000;
}
