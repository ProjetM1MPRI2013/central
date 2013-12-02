#include "ScenarioActionList.h"


/*****************
 *ChangeDirection*
 *****************/
ChangeDirection::ChangeDirection(int id, int mov) : ScenarioAction ("ChangeDirection"){
  playerID = id;
  newMovement = mov;
};

void ChangeDirection::run(){
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
  return;
};
