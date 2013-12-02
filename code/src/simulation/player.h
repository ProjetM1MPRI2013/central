#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "SFML/System.hpp"
#include <iostream>
#include <cerrno>

enum Direction {UP, UPRIGHT, RIGHT, RIGHTDOWN, DOWN, DOWNLEFT, LEFT, LEFTUP, STOP};

class Player{
public:
  int getID();
  Position* getPosition();
  Direction getDirection();
  void setDirection(Direction d);

  /**
   * @brief Update the position of the player
   * Calculate the new position after a  movement in the direction (Direction d) during a time (sf::Time dt)
   */
  void updatePosition(sf::Time dt);

  Player(int id, float x, float y);

private:
  /**
   * @brief Identifier of the player
   * 0 for the Chief of the Police, > 0 for the terrorists
   */
  int playerID;
  float speed;
  Position p;
  Direction d;
};

#endif
