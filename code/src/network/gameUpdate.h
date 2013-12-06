#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H

#include <string>
#include "abstractMessage.h"

/**
 * @brief The GameUpdate class
 * Will contain informations to transmit to the clients
 * Will be created from the GameState.
 */

class GameUpdate : public AbstractMessage{
public:
    GameUpdate();
    static std::string getMsgType(){
      return "" ;
    }

    static GameUpdate& fromString(std::string& data) ;

    std::string& toString(){
      return *(new std::string()) ;
    }
    GameUpdate * copy(){
    return NULL ;}
};

#endif // GAMEUPDATE_H
