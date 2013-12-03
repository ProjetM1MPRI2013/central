#ifndef NPCUPDATE_H
#define NPCUPDATE_H
#include "simulation/position.h"
#include "simulation/npc.h"
#include <boost/uuid/uuid.hpp>

/**
 * @brief The NpcUpdate class : Container for informations that will be passed as an update through the network.
 */
class NpcUpdate
{
public:
  /**
   * @brief NpcUpdate : creates an update from the given NPC
   * @param npc : the npc to store informations about.
   */
  NpcUpdate(NPC npc);

  boost::uuids::uuid id ;
  Position currentPosition ;
  float fear ;
  bool shocked ;
  float speed ;
};

#endif // NPCUPDATE_H
