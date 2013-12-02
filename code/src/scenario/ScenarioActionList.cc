#include "ScenarioActionList.h"


/*****************
 *ChangeDirection*
 *****************/
ChangeDirection::ChangeDirection(int id, Direction mov) : ScenarioAction ("ChangeDirection"){
  playerID = id;
  newMovement = mov;
};

void ChangeDirection::run(){
  simulation->getPlayerByID(playerID)->setDirection(newMovement);
  return;
};

/***********
 *Explosion*
 ***********/
Explosion::Explosion(Tile* t,int p) : ScenarioAction("Explosion"){
  location = t;
  power = p;
};

void Explosion::run(){
  return;
};

/*********
 *KillNPC*
 *********/
KillNPC::KillNPC(NPC* t) : ScenarioAction("KillNPC"){
  target = t;
};

void KillNPC::run(){
  //Supprime un NPC de la case du NPC target, vue qu'il n'existe pas de methode pour supprimer un NPC précis -_-' [Adrien K]
  //TODO : gérer le cas ou le NPC n'existe pas
    simulation->supprimerNPC(simulation->isInTyleX(target),simulation->isInTyleY(target));
  return;
};
