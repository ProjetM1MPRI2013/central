#include "npcUpdate.h"

NpcUpdate::NpcUpdate(NPC npc) :/* id(npc.getUuid()),*/ currentPosition(npc.getPosition()),
  fear(npc.getFear()), shocked(npc.isShocked()), speed(npc.getSpeed())
{
}
