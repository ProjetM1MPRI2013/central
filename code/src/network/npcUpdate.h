#ifndef NPCUPDATE_H
#define NPCUPDATE_H

#include <boost/uuid/uuid.hpp>

#include "simulation/position.h"

class NPC ;
class GraphicContextIso ;


/**
 * @brief The NpcUpdate class : Container for informations that will be passed as an update through the network.
 * @author mheinric
 */
class NpcUpdate : public AbstractMessage
{
public:
  /**
   * @brief NpcUpdate : creates an update from the given NPC
   * @param npc : the npc to store informations about.
   */

  NpcUpdate(NPC& npc, bool isCreated = true);


  /**
   * @brief createNpc : creates a new NPC according to this update.
   *
   * The field isCreated must be true. If it is not, it will fail.
   * @param gra : the graphicContextIso to search the texturePack
   * @return A newly created NPC which should be a copy of the one it was created from.
   */
  NPC * createNpc(GraphicContextIso* gra) ;


  /**
   * @brief isCreated : true if this message correspond to the creation of the NPC
   */
  bool isCreated ;

  /*
   * The following fields corresponds to those of the NPC class
   */
  boost::uuids::uuid id ;

  Position currentPosition ;
  Position target;
  float fear;
  bool shocked;
  float speed;
  float hitboxSize;
  float deltaT ;
  float lambda ;
  float Vzero ;
  bool dying;
  bool dead;
  // a float, corresponding to the time in seconds (to avoid problems for serialization)
  float deathTimeout;

  int textPackID ;


  static std::string getMsgType() { std::string s = std::string("NpcUpdate") ; s.resize(8) ; return s ;}
  NpcUpdate* copy() ;

  NpcUpdate() ;


private :
  friend class boost::serialization::access ;
  template <class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & boost::serialization::base_object<AbstractMessage>(*this);
    ar & isCreated ;
    __serialize_variables(ar, id, currentPosition, target, fear, shocked, dying, dead, deathTimeout) ;
    if(isCreated)
      __serialize_variables(ar, speed, hitboxSize, deltaT, lambda, Vzero, textPackID) ;
  }
};

#endif // NPCUPDATE_H
