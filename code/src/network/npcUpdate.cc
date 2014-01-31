#include "npcUpdate.h"

#include "simulation/position.h"
#include "simulation/npc.h"

/*
 * @author mheinric
 */

NpcUpdate::NpcUpdate(NPC &npc) : id(npc.getUuid()), currentPosition(npc.getPosition()),
  fear(npc.getFear()), shocked(npc.isShocked()), speed(npc.getSpeed())
{
}
