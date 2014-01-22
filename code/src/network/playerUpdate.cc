#include "playerUpdate.h"

#include "simulation/player.h"

PlayerUpdate::PlayerUpdate(): player_id(0), pos(0,0){
}

PlayerUpdate::PlayerUpdate(Player &player) : player_id(player.getID()), pos(*player.getPosition())
{
}
