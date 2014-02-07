/**
 * @author: Joseph
 */
#ifndef POSITIONABLE_H
#define POSITIONABLE_H
#include "position.h"
#include "graphism/fogDisabler.h"
#include "eventSource.h"

/**
 * @brief The Positionable class
 * it only contains a Position and methods to get and set it
 */
class Positionable : public FogDisabler, public EventSource {
 protected:
  Position position;


 public:
//  using EventSource::EventSource;

  /**
   * @brief Positionable
   * the default constructor, creates a new Positionable with the default position
   */
  Positionable();

  /**
   * @Brief Positionable
   * the default constructor with a given uuid passed to EventSource
   */
  Positionable(boost::uuids::uuid uuid);


  /**
   * @brief Positionable
   * creates a new Positionable with position (x,y)
   * @param x : the x coordinate
   * @param y : the y coordinate
   */
  Positionable(float x,float y);

  /**
   * @brief Positionable
   * creates a new Positionable with a given Position
   * @param p : the Position
   */
  Positionable(Position& p);

  /**
   * @brief getPosition
   * @return the Positionable's Position as a reference
   */
  virtual Position& getPosition();

  /**
   * @brief setPosition
   * sets the Positionable's Position
   * @param p : the new Position as a reference (the Positionable's Position will be the same object)
   */
  virtual void setPosition(Position& p);
};
#endif
