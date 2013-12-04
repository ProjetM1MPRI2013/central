#include "updateGenerator.h"

UpdateGenerator::UpdateGenerator(Simulation& globalState, Server& server) :
  globalState(&globalState), server(&server)
{
}


void UpdateGenerator::update(){
  //Récupérer tous les players
  //Pour chaque player générer l'update correspondante
  //Et envoyer l'update.
}

GameUpdate* generateUpdate(Player& player) {
  return NULL ;
}
