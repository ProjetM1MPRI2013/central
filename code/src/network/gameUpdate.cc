#include "gameUpdate.h"

GameUpdate::GameUpdate(){}

GameUpdate& GameUpdate::fromString(std::string &data){
    return *(new GameUpdate()) ;
}
