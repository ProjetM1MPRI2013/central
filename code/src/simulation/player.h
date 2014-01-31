/**
   @author: Adrien K.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "Stuff.h"
#include "SFML/System.hpp"
#include <iostream>
#include <memory>
#include <cerrno>
#include <exception>
#include <list>
#include <stdexcept>
#include "positionable.h"

enum Direction {UP, UPRIGHT, RIGHT, RIGHTDOWN, DOWN, DOWNLEFT, LEFT, LEFTUP, STOP, ERROR};

class StuffNotFound : public std::runtime_error
{
  public:
  explicit StuffNotFound();
};

class Player : public Positionable{
public:

  //Pour débugue
  int isServer = 0;

  int getID();

  Direction getDirection();
  void setDirection(Direction d);

  std::vector<int> getInventory(); // returns list of stuff ids currently held by the player
  template <class T>
  T getItemByID(int stuffID); // raises exception if Stuff not found
  bool hasItemByID(int stuffID);
  void addItem(Stuff&& s);
  void removeItem(int stuffID);

  /**
   * @brief Update the position of the player
   * Calculate the new position after a  movement in the direction (Direction d) during a time (sf::Time dt)
   */
  void updatePosition(sf::Time dt,Geography& map);

  Player(int id, float x, float y);

  /**
   * @brief Disable copy constructor
   * We want players to be globally unique and other classes to always access
   * their most recent version.
   * It is still possible to access Players by reference:
   *
   *   Player& p = simulation->getPlayerByID(someID);
   *
   */
  // FIXME I cannot delete the copy-constructor for now because gcc yells at me
  // since Simulation has a destructor. I don't understand why yet.
  //Player(const Player& other) = delete;
  Player(const Player& other);
  Player(Player&& other) = default;
  ~Player() = default;


private:
  /**
   * @brief Identifier of the player
   * 0 for the Chief of the Police, > 0 for the terrorists
   */
  int playerID;
  float speed;
  Direction d;
  /**
   * @brief The inventory is polymorphic so it holds pointers
   */
  std::list<std::unique_ptr<Stuff>> inventory;

};

template <typename T>
T Player::getItemByID(int stuffID) {
  for (auto& stuffPtr : inventory) {
     /*
      * Not sure how casting works for copy constructors and unique_ptrs:
      * let's say B derives A, and you want to create a new instance of A from
      * a unique_ptr<B>. Well, implicit casting from 'unique_ptr<B>' to 'const A&' 
      * does not work. That's why I'm casting manually.
      */
    if (stuffPtr->stuffID == stuffID) { return T(*(static_cast<T*>(stuffPtr.get()))); }
  }
  throw StuffNotFound();
}
#endif
