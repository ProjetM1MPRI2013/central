#include "npcUpdate.h"

#include "simulation/position.h"
#include "simulation/npc.h"
#include "graphism/graphic_context_iso.h"

/*
 * @author mheinric
 */

NpcUpdate::NpcUpdate() : isCreated(false), id(),
  currentPosition(), target(), fear(),
  shocked(false), speed(), hitboxSize(), deltaT(), lambda(), Vzero(),
  dying(), dead(), deathTimeout(), textPackID()
{
}


NpcUpdate::NpcUpdate(NPC &npc, bool is_created) : isCreated(is_created), id(npc.uuid), currentPosition(npc.position), target(npc.target),
  fear(npc.getFear()), shocked(npc.isShocked()), speed(npc.getSpeed()),
  hitboxSize(npc.hitboxSize), deltaT(npc.deltaT), lambda(npc.lambda), Vzero(npc.Vzero),
  dying(npc.dying), dead(npc.dead), deathTimeout(npc.deathTimeout.asSeconds()), textPackID(npc.anim.getTexID())
{
}

NpcUpdate* NpcUpdate::copy(){
  return new NpcUpdate(*this) ;
}

NPC* NpcUpdate::createNpc() {
  assert(isCreated) ;
  NPC* npc = new NPC(speed, fear, hitboxSize, currentPosition, textures::get(textPackID), id);
  npc->position = currentPosition ;
  npc->shocked = shocked ;
  npc->speed = speed ;
  npc->deltaT = deltaT ;
  npc->lambda = lambda ;
  npc->Vzero = Vzero ;
  npc->dying = dying ;
  npc->dead = dead ;
  npc->deathTimeout = sf::seconds(deathTimeout) ;
  return npc ;
}

void NpcUpdate::updateNpc(NPC& npc) {
  assert(!isCreated) ;
  npc.speed = speed;
  npc.setFear(fear);
  npc.hitboxSize = hitboxSize;
  npc.setPosition(currentPosition) ;
  npc.setShocked(shocked);
  npc.speed = speed ;
  npc.deltaT = deltaT ;
  npc.lambda = lambda ;
  npc.Vzero = Vzero ;
  npc.dying = dying ;
  npc.dead = dead ;
  npc.deathTimeout = sf::seconds(deathTimeout) ;
  /*
  * FIXME updating texture anim doesn't work.
  * Inferno cops become invisible on the client
  * npc.TextureAnim(textures::get(textPackID));
  */
}
