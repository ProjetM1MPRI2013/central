#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
//class Simulation;
//#include "simulation.h"
//#include "scenario/Stuff.h"
class Stuff;
#include "SFML/System.hpp"
#include <iostream>
#include <cerrno>
#include <list>

enum Direction {UP, UPRIGHT, RIGHT, RIGHTDOWN, DOWN, DOWNLEFT, LEFT, LEFTUP, STOP, ERROR};

class Player{
public:

  //Pour débugue
  int isServer = 0;

  int getID();
  Position* getPosition();

  Direction getDirection();
  void setDirection(Direction d);

  std::list<Stuff*> getInventory();
  void addItem(Stuff* s);
  void removeItem(Stuff* s);
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
  std::list<Stuff*> inventory;
};

#endif
