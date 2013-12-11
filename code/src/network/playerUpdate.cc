#include "playerUpdate.h"

#include "simulation/player.h"

PlayerUpdate::PlayerUpdate(): pos(0,0){
}

PlayerUpdate::PlayerUpdate(Player &player) : pos(*player.getPosition())
{
}
