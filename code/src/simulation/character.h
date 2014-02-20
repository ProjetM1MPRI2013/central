/**
 * @author: Joseph
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include "trajectory.h"
#include "positionable.h"
#include "position.h"
#include "withUuid.h"
#include <cmath>
#include "boost/uuid/uuid_serialize.hpp"
#include <utility>


class Character : public Positionable {
 protected:
  Trajectory trajectory;
  Position start;
  Position target;
  float speed;
  float deltaT = 1;
  float lambda = 1;
  float Vzero = 10;

 public:

  /**
   * @brief Character
   * creates a new Character
   * @param s : the Character's speed
   * @param start : the Character's start position
   */
  Character(float s,Position& start);


  /**
   * @brief Character
   * creates a new Character with a given uuid
   * @param s : the Character's speed
   * @param start : the Character's start position
   * @param uuid: the uuid
   */
  Character(float s,Position& start,boost::uuids::uuid uuid);

  /**
   * @brief getSpeed
   * @return the Character's speed
   */
  float getSpeed() const;
  
  /**
   * @brief getTrajectory
   * @return the NPC's Trajectory as a reference
   */
  Trajectory& getTrajectory();


  /**
   * @brief setTrajectory
   * sets the NPC's trajectory
   * (the server shouldn't use it)
   * @param t : the new trajectory
   */
  void setTrajectory(Trajectory& t);

  /**
   * @brief setSpeed
   * sets the NPC's speed
   * @param s : the new speed
   */
  void setSpeed(float s);

  /**
   * @brief updatePosition
   * updates the Character's position
   * ie tells him to move towards his target for a small time interval
   * @param dt : the time interval during which the Character will move
   * @param map : the map on which the Character moves
   */
  virtual void updatePosition(sf::Time dt,Geography& map) = 0;

  /**
   * @brief potential
   * computes the potential created by the Character
   * @param p: the Position where the potential will be evaluated
   */
  float potential(Position p);

  /**
   * @brief gradPotential
   * computes the gradient of the Character's potential
   * @param p: the Position where the gradient will be computed
   */
  std::pair<float,float> gradPot(Position p);

  /**
   * @brief getTarget
   * @return the Character's target position
   */
  Position getTarget() const;

  /**
   * @brief setTarget
   * sets a new target position for the Character and recomputes his trajectory
   * @param t: the new target position
   * @param map: the map which will be used for the pathfinding
   */
  virtual void setTarget(Position t,Geography& map) = 0;

  /**
   * @brief hasArrived
   * @return true iff the NPC has arrived at his target position
   */
  bool hasArrived();

 protected:
  Character() {};
};


#endif
