#ifndef PLAYERUPDATE_H
#define PLAYERUPDATE_H
#include "simulation/position.h"


class Player ;

class PlayerUpdate
{
public:

  /**
   * @brief PlayerUpdate : default constructor, builds an update with arbitrary values.
   */
  PlayerUpdate() ;
  /**
   * @brief PlayerUpdate : creates a new update from the player Data.
   * @param player
   */
  PlayerUpdate(Player &player);

  int player_id ;
  Position pos ;
};

#endif // PLAYERUPDATE_H
