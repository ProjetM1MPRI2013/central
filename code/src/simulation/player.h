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
#include "drawableObject.h"
#include "NewMov.h"
enum MovementType { DESTINATION, DIRECTION };
class StuffNotFound : public std::runtime_error
{
public:
	explicit StuffNotFound();
};

class Player : public Positionable, public DrawableObject {
public:

	//Pour débugue
  int isServer = 0;
  
  int getID() const;
  
  Direction getDirection() const;
  
  /**
   * @brief This method sould only be used by server
   * @param d : the new direction of the player
   * @param timeStamp : the timeStamp of the direction changement
   */
  void setDirection(Direction d, int timeStamp);
  
  /**
   * @brief This method sould only be used by server
   * @param d : the new destination of the player
   * @param timeStamp : the timeStamp of the direction changement
   */
  void setDestination(Position pos, int timeStamp);

  /**
   * @brief This method sould only be used by client
   * @param d : the new direction of the player
   */
  void setDirection(Direction d);

  /**
   * @brief This method sould only be used by client
   * @param d : the new direction of the player
   */
  void setDestination(Position pos);

	std::vector<int> getInventory(); // returns list of stuff ids currently held by the player
  /*
   * Get a reference to the inventory item with ID ClickableID.
   * If you store this reference, it may become invalid later.
   * See note for future improvement above implementation
   */
	template <class T>
	T& getItemByID(int ClickableID); // raises exception if Stuff not found
	bool hasItemByID(int ClickableID);
	template <class T>
	void addItem(T&& s);
	void removeItem(int ClickableID);

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
  Position destination;
  MovementType movementType;

  /**
   * @brief The last timestamp of a NewMovNetwork message accepted
   */
  int lastTimeStamp;

  /**
   * @brief The inventory is polymorphic so it holds pointers
   */
	std::list<std::unique_ptr<Clickable>> inventory;

};
template <typename T>
 void Player::addItem(T&& stuff) { // && has a different meaning now!
 	this->inventory.push_back(std::unique_ptr<Clickable>(new T(stuff)));
 	//DBG << "Add item to player " << this->playerID << " : " << stuff.name;
 	return;
 };



/*
* Note for future improvement: 
*
* Ideally we want to return a copy of the found item, but some items derive a
* class B which has undefined virtual methods. So you can't say get<B>(id)
* because B is not constructible.
*
* A solution would be to use "virtual constructors", 
*
* - either by defining a clone() method on all classes deriving B :
* http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Virtual_Constructor
*
* - or by defining a generic close on B, and making all D classes derive B<D>:
*   http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern#Polymorphic_copy_construction
*/
template <typename T>
T& Player::getItemByID(int ClickableID) {
	for (auto& stuffPtr : inventory) {
		if (stuffPtr->ClickableID == ClickableID) { 
      return (*(static_cast<T*>(stuffPtr.get())));
    }
	}
	throw StuffNotFound();
}
#endif
