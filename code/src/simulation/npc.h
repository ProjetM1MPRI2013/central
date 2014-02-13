/**
 * @author: Joseph
 */
#ifndef NPC_H
#define NPC_H
#include "trajectory.h"
//#include "simulation.h"
#include "positionable.h"
#include "position.h"
#include "withUuid.h"
#include "eventSource.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "graphism/drawableObject.h"
#include <cmath>


/**
 * @brief The NPC class
 * It represents a NPC
 */

class NPC : public Positionable, public DrawableObject {
 private:
  Trajectory trajectory;
  Position target;
  float fear;
  bool shocked;
  float speed;
  float hitboxSize;
  float deltaT = 1;
  float lambda = 1;
  float Vzero = 10;


 public:
  /**
   * @brief NPC
   * Creates a new NPC
   * (initially not shocked)
   * @param s : the NPC's speed
   * @param f : the NPC's initial fear level
   * @param h : the NPC's hitbox size
   * @param start : the NPC's start position
   * @param tex: the texture pack of the sprite sheet of the animation
   */
  NPC(float s,float f,float h,Position& start,TexturePack* tex);

  /**
   * @brief NPC
   * Creates a new NPC with an empty trajectory and a given uuid
   * (for the client, since creating the trajectory would compute the pathfinding)
   * @param s : the NPC's speed
   * @param f : the NPC's initial fear level
   * @param h : the NPC's hitbox size
   * @param tex: the texture pack of the sprite sheet of the animation
   * @param uuid: the uuid for the NPC
   */
  NPC(float s,float f,float h,TexturePack* tex,boost::uuids::uuid uuid);


  /**
   * @brief NPC
   * creates a new NPC by copying an existing one
   * @param n: the NPC to copy
   */
  NPC(const NPC& n);

  virtual ~NPC() = default;

  /**
   * @brief getFeat
   * @return the NPC's fear level
   */
  float getFear() const;

  /**
   * @brief setFear
   * set the NPC's fear level
   * @param f : the new fear level
   */
  void setFear(float f);

  /**
   * @brief isShocked
   * @return : true if the NPC is shocked, false otherwise
   */
  bool isShocked() const;

  /**
   * @brief setShocked
   * sets the NPC's shocked boolean
   * @param s : the new value of shocked
   */
  void setShocked(bool s);

  /**
   * @brief getSpeed
   * @return the NPC's speed
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
   * @brief getPosition
   * @return the NPC's position as a reference
   */
  Position& getPosition();

  /**
   * @brief setPosition
   * sets the NPC's current position
   * this method should NOT be used with updatePosition, since it already changes the current position
   * the server should use updatePosition to move the NPCs
   * @param the new position as a reference, so the NPC's new position will be the same object
   */
  void setPosition(Position& p);

  /**
   * @brief updatePosition
   * updates the NPC's position
   * ie tells him to move towards his target for a small time interval
   * @param dt : the time interval during which the NPC will move
   * @param map : the map on which the NPC moves
   */
  void updatePosition(sf::Time dt,Geography& map);

  /**
   * @brief isInHitbox
   * tells if a position is within the NPC's hitbox
   * @param p : a position
   * @return true iff the position is in the hitbox
   */
  bool isInHitbox(Position& p);

  /**
   * @brief getHitboxSize
   * @return the NPC's hitbox size
   */
  float getHitboxSize() const;

  /**
   * @brief hasArrived
   * @return true iff the NPC has arrived at his target position
   */
  bool hasArrived();
  
  /**
   * @brief setAnim
   * Sets the animation of the NPC
   * @param t: New animation
   **/  
  void setAnim(const AnimType t);

  /**
   * @brief potential
   * computes the potential created by the NPC
   * @param p: the Position where the potential will be evaluated
   */
  float potential(Position p);

  /**
   * @brief gradPotential
   * computes the gradient of the NPC's potential
   * @param p: the Position where the gradient will be computed
   */
  std::pair<float,float> gradPot(Position p);

  /**
   * @brief nextFrame
   * Changes the state of the animation to the next frame, according to the
   * different parametters of the NPC.
   */
  void nextFrame();

  /**
   * @brief getTarget
   * @return the NPC's target position
   */
  Position getTarget() const;

  /**
   * @brief setTarget
   * sets a new target position for the NPC and recomputes his trajectory
   * @param t: the new target position
   * @param map: the map which will be used for the pathfinding
   */
  void setTarget(Position t,Geography& map);

private :
  /**
   * @brief NPC : default constructor used only for serialization
   */
  NPC(){} ;

  SIMPLE_SERIALIZATION(position, target, fear, shocked, speed, hitboxSize, deltaT, lambda, Vzero )
};
#endif
