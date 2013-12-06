#include "localState.h"

LocalState::LocalState(Player* _player, Simulation* _simul) :
  local_map ( * (_simul->getMap())){
  owner_player = _player;
  //view_range = _player->getViewRange();
  view_range = 10;
  parent_sim = _simul;
  //TODO {denys} : receive rights to map;
  //local_map = _simul->getMap();

  /*initialization of the local_viewed*/
  potential_viewed = new Tile** [2*view_range+1];
  for (int i = 0; i < 2*view_range+1; ++i)
     potential_viewed[i] = new Tile* [2*view_range+1];
  rebuildLocalMap();
}

float LocalState::getLocalTime(){
  return localtime_ms;
}

Tile*** LocalState::getViewedTiles(Layers l){
  return potential_viewed;
}

void LocalState::rebuildLocalMap(){
  int absciss = owner_player->getPosition()->isInTile(local_map).getCoord().getAbs();
  int ordinat = owner_player->getPosition()->isInTile(local_map).getCoord().getOrd();
  int x,y;
  for (int i = 0; i < 2*view_range+1; ++i)
   for (int j = 0; j < 2*view_range+1; ++j){
        x = absciss - view_range + i;
        y = ordinat - view_range + j;
        potential_viewed[i][j] = local_map.getTile(x,y);
     }
}

Tile* LocalState::getRelativePlayerTile(int x, int y){
  int absciss = owner_player->getPosition()->isInTile(local_map).getCoord().getAbs();
  int ordinate = owner_player->getPosition()->isInTile(local_map).getCoord().getOrd();
  if ((abs(x) <= view_range) && (abs(y) <= view_range)){
      return potential_viewed[absciss+x][ordinate+y];
    }
  else {
      return NULL;//TODO : assert
    }
}

Player* LocalState::getPlayerLocalState(){
  return owner_player;
}

Tile& LocalState::getTile(Position p, Layers l){
  return p.isInTile(local_map);
}

void LocalState::update(){
  rebuildLocalMap();
  //TODO {denys} : remove this fake timer
  localtime_ms +=1000;
}
