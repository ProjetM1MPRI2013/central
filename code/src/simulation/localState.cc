/**
  *@author Denys KANUNIKOV,
  */
#include "localState.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include "network/netEvent.h"
#include "scenario/NewMov.h"
#include "scenario/ScenarioActionList.h"
#include "scenario/HScenario.h"

#define DEBUG false

#include "debug.h"

/* Never used
LocalState::LocalState(std::string _seed, Player& _player)
    : Simulation(_seed, std::vector<Player*>()),
  owner_player(_player){
  addPlayer(&owner_player);
  isServer = false;
  map = (Geography*) new Generation1(_seed);
}
*/

LocalState::LocalState(Geography* map,int nbPlayers,int id) :
    Simulation(map, nbPlayers, id),
    client(NULL),
    owner_player(getPlayerByID(id)){
    isServer = false;
}

sf::Time &LocalState::getLocalTime(){
  return localtime;
}

/**
 * @brief LocalState::getRelativePlayerTile
 * @param x : number of tiles to the right from the players position
 * @param y : number of tiles to the top from the players position
 * @return a reference to a Tile if on map, or owner's tile otherwise
 */
Tile& LocalState::getRelativePlayerTile(int x, int y){
  int absciss = owner_player.getPosition().isInTile(*map).getCoord().getAbs();
  int ordinate = owner_player.getPosition().isInTile(*map).getCoord().getOrd();
  absciss += x;
  ordinate += y;
  if ((absciss < map->getMapWidth()) && (absciss >= 0)
       && (ordinate < map->getMapHeight()) && (ordinate >= 0)){
      return map->getTileRef(absciss, ordinate);
    }
  else {
      return owner_player.getPosition().isInTile(*map);
    }
}

/**
 * @brief LocalState::getOwner
 * @return  reference to the owner
 */
Player& LocalState::getOwner(){
  return owner_player;
}

Tile& LocalState::getTile(Position p, Layers l){
  return p.isInTile(*map);
}

//Nobody je rajoute ça :
std::pair<int,int> LocalState::getCurrentTile(){
	Player* p = this->getPlayer();
	Position& pos = p->getPosition();
	Geography* map = this->getMap();
	Tile& t = pos.isInTile(*map);
	std::pair<int,int> pr (t.getCoord().abs,t.getCoord().ord);
	return pr;
	;};

void LocalState::run(sf::Time dt){
//  int chance;
  //Adrien K. normalement ça devrait être bon.
  //If their is no enough money, remove an agent and a camera
  if (sous[0] < 0) {
      if (!agents.empty()){
          agents.pop_back();}
      if (!cameras.empty()){
          cameras.pop_back();}
  }

   //The client retrieve all the new messages from the network (of type ScenarioAction), and add them to the list of pending ScenarioAction
  std::vector<ScenarioAction *> scenarioActionFromNetwork = this->client->receiveMessages<ScenarioAction>();
  for (ScenarioAction* action: scenarioActionFromNetwork){
      DBG << "Client : add a ScenarioAction from network of type " << action->name ;
      action->simulation = this;
      this->addAction(action);
  }

  for (ScenarioAction* action: pendingActions) {
      std::cout << "Client : applying pending Scenario Action of type " << action->name<< std::endl;
      action->run();
      std::cout << "nobody client fin run " << std::endl;

  }



  this->pendingActions.clear();

  //On supprime les actions déjà traitées
  this->toDelete.clear();

  /*on empile les dt jusqu'à obtenir plus d'une seconde*/
  this->smallTime = smallTime + dt.asSeconds();

  /*on compte le nombre de secondes dans dt*/
  int secondes = floor(smallTime);
  smallTime = smallTime - secondes;

  /* We update the position of all the players */
  for (Player& player : players) { player.updatePosition(dt,*map); }

  /*on n'effectue pas le lissage de la matrice plus d'une fois par seconde*/
        for (int i = 0; i < secondes; i++) {
          this->lisserMatrice();
        }

  /*on fait payer l'entretien des différents trucs*/
  for (int i = 1; i < secondes; i++) {
      for (Agent* agent: agents) {
          sous[0] = sous[0] - agent->getEntretien();
      }

      for (Camera* camera: cameras) {
          sous[0] = sous[0] - camera->getEntretien();
        }
      }

  //Deplacement de tous les NPCs.
  for (NPC *npc : NPCs) {
      bool wasArrived = npc->hasArrived();
      Tile& tileBefore = npc->getPosition().isInTile(*map);
      npc->updatePosition(dt, *map);
      Tile& tileAfter = npc->getPosition().isInTile(*map);
      if (!tileBefore.equals(tileAfter)) {
          tileBefore.removeNPC(npc);
          tileAfter.addNPC(npc);
      }
      // Juste un test pour le EventManager (activer debug dans HScenario.cc pour le voir_
      if (npc->hasArrived() && !wasArrived) {
          (*npc).trigger("NPC::arrived");
      }
      if (DEBUG) {
          std::list<NPC*> neighbours = npc->getPosition().isInTile(*map).getNotTooFarNPCs(*map);
          while (!neighbours.empty()) {
              NPC* tempNPC = neighbours.front();
              neighbours.pop_front();
              if (tempNPC->getUuid()!= npc->getUuid()) {
                  const std::string id1 = boost::lexical_cast<std::string>(npc->getUuid());
                  const std::string id2 = boost::lexical_cast<std::string>(tempNPC->getUuid());
                  printf("NPC %s: neighbour %s\n",id1.c_str(),id2.c_str());
              }
          }
      }
  }

  DBG << "LocalState : Position of the Player" << getOwner().getPosition() ;

  client->update(dt);
  return;
}

void LocalState::setClient(Client* c) {
  client = c;
  c->setLocalState(this);
  return;
}

Client* LocalState::getClient(){
  return client;
}

