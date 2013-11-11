#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H

#include<string>

/**
 * @brief The GameUpdate class
 * Will contain informations to transmit to the clients
 * Will be created for the GameState.
 */

class GameUpdate{
public:
    GameUpdate();
    static GameUpdate& fromString(std::string& data) ;
};

#endif // GAMEUPDATE_H
