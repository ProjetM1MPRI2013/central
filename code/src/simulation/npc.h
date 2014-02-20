/**
 * @author: Joseph
 */
#ifndef NPC_H
#define NPC_H
#include "character.h"
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
#include "boost/uuid/uuid_serialize.hpp"
#include <utility>

/**
 * @brief The NPC class
 * It represents a NPC
 */

class NPC : public Character, public DrawableObject, public AbstractMessage {
 private:
  /*needed for seriliazation*/
  float fear;
  bool shocked;
  float hitboxSize;
  bool dying;
  bool dead;
  sf::Time deathTimeout;


 public:
//  static std::string getMsgType() { return "NPC_msg" ; }
  virtual AbstractMessage* copy() {
      std::cout << "ERROR: NPC: we can't copy this class!\n" ;
    return NULL ;
  }

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
  NPC(float s,float f,float h,Position& start, TexturePack* tex,
      boost::uuids::uuid uuid);

  /**
   * @brief NPC
   * creates a new NPC by copying an existing one
   * @param n: the NPC to copy
   */
  NPC(const NPC& n) = delete;

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
   * @brief isDying
   * @return : true if the NPC is dying, false otherwise
   */
  bool isDying();

  /**
   * @brief isDead
   * @return : true if the NPC is dead, false otherwise
   */
  bool isDead();

  /**
   * @brief setShocked
   * sets the NPC's shocked boolean
   * @param s : the new value of shocked
   */
  void setShocked(bool s);


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
   * @brief setAnim
   * Sets the animation of the NPC
   * @param t: New animation
   **/  
  void setAnim(const AnimType t);


  /**
   * @brief nextFrame
   * Changes the state of the animation to the next frame, according to the
   * different parametters of the NPC.
   */
  void nextFrame();


  /**
   * @brief setTarget
   * sets a new target position for the NPC and recomputes his trajectory
   * @param t: the new target position
   * @param map: the map which will be used for the pathfinding
   */
  void setTarget(Position t,Geography& map);

  /**
   * @brief kill
   * kills the npc, ie tells him he is dying
   */
  void kill();

  Position& getPosition();

  void setPosition(Position& p);



private :
  /**
   * @brief NPC : default constructor used only for serialization
   */
  NPC(){} ;

  friend class NpcUpdate ;

//  SIMPLE_SERIALIZATION(uuid, position, target, fear, shocked, speed, hitboxSize, deltaT, lambda, Vzero )
  SIMPLE_MESSAGE(NPC, AbstractMessage, uuid, position,
                 target, fear, shocked, speed, hitboxSize, deltaT, lambda, Vzero )
};

std::ostream& operator<<(std::ostream& os, const NPC& npc);
#endif
