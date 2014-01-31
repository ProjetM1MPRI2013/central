#ifndef NPCUPDATE_H
#define NPCUPDATE_H

#include <boost/uuid/uuid.hpp>

#include "simulation/position.h"

class NPC ;


/**
 * @brief The NpcUpdate class : Container for informations that will be passed as an update through the network.
 * @author mheinric
 */
class NpcUpdate
{
public:
  /**
   * @brief NpcUpdate : creates an update from the given NPC
   * @param npc : the npc to store informations about.
   */
  NpcUpdate(NPC& npc);

  boost::uuids::uuid id ;
  Position currentPosition ;
  float fear ;
  bool shocked ;
  float speed ;
};

#endif // NPCUPDATE_H
