#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H

#include<string>

class GameUpdate{
public:
    GameUpdate();
    static GameUpdate& fromString(std::string& data) ;
};

#endif // GAMEUPDATE_H
