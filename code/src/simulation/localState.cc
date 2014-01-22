#include "localState.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include "network/netEvent.h"
#include "scenario/NewMov.h"
#include "scenario/ScenarioActionList.h"
#include "scenario/HScenario.h"

#define DEBUG false

#include "debug.h"


LocalState::LocalState(std::string _seed, const Player& _player)
    : Simulation(_seed, std::vector<Player*>()),
  owner_player(_player){
  addPlayer(&owner_player);
  isServer = false;
  map = (Geography*) new Generation1(_seed);
}

LocalState::LocalState(Geography* map,int nbPlayers,int id) :
    Simulation(map, nbPlayers, id),
    owner_player(*getPlayerByID(id)){
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
  int absciss = owner_player.getPosition()->isInTile(*map).getCoord().getAbs();
  int ordinate = owner_player.getPosition()->isInTile(*map).getCoord().getOrd();
  absciss += x;
  ordinate += y;
  if ((absciss < map->getMapWidth()) && (absciss >= 0)
       && (ordinate < map->getMapHeight()) && (ordinate >= 0)){
      return map->getTileRef(absciss, ordinate);
    }
  //TODO {Denys} : think about returning meaning
  else {
      return owner_player.getPosition()->isInTile(*map);
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
  for (std::vector<ScenarioAction *>::iterator it = scenarioActionFromNetwork.begin(); it !=  scenarioActionFromNetwork.end(); ++it){
      std::cout << "Client : add a ScenarioAction from network of type " << (*it)->name << "\n";
      (*it)->simulation = this;
      this->addAction(*it);
  }

  for (std::list<ScenarioAction*>::iterator it = pendingActions.begin();
       it != pendingActions.end(); ++it) {
      ScenarioAction* action = (*it);
      if (DEBUG) std::cout << "Client : applying pending Scenario Action of type " << action->name << "\n";
      action->run();
  }
  this->pendingActions.clear();

  //On supprime les actions déjà traitées
  this->toDelete.clear();

  /*on empile les dt jusqu'à obtenir plus d'une seconde*/
  this->smallTime = smallTime + dt.asSeconds();

  /*on compte le nombre de secondes dans dt*/
  int secondes = floor(smallTime);
  smallTime = smallTime - secondes;

  /*on n'effectue pas le lissage de la matrice plus d'une fois par seconde*/
  /*  for (int i = 1; i < secondes; i++) {
   *        this->lisserMatrice();
   *        }*/

  /* We update the position of all the players */
  for (std::list<Player*>::iterator it = players.begin(); it != players.end();
       ++it) {(*it)->updatePosition(dt);
  }

  /*on fait payer l'entretien des différents trucs*/
  for (int i = 1; i < secondes; i++) {
      for (std::list<Agent*>::iterator it = agents.begin();
           it != agents.end(); ++it) {
          sous[0] = sous[0] - (*it)->getEntretien();
      }

      for (std::list<Camera*>::iterator it = cameras.begin();
           it != cameras.end(); ++it) {
          sous[0] = sous[0] - (*it)->getEntretien();
        }
      }

  //Deplacement de tous les NPCs.
  for (std::list<NPC *>::iterator it = NPCs.begin(); it != NPCs.end(); ++it) {
      bool wasArrived = (*it)->hasArrived();
      Tile& tileBefore = (*it)->getPosition().isInTile(*map);
      (*it)->updatePosition(dt, *map);
      Tile& tileAfter = (*it)->getPosition().isInTile(*map);
      if (!tileBefore.equals(tileAfter)) {
          tileBefore.removeNPC(*it);
          tileAfter.addNPC(*it);
      }
      // Juste un test pour le EventManager (activer debug dans HScenario.cc pour le voir_
      if ((*it)->hasArrived() && !wasArrived) {
          (**it).trigger("NPC::arrived");
      }
      if (DEBUG) {
          std::list<NPC*> neighbours = (*it)->getPosition().isInTile(*map).getNotTooFarNPCs(*map);
          while (!neighbours.empty()) {
              NPC* tempNPC = neighbours.front();
              neighbours.pop_front();
              if (tempNPC->getUuid()!= (*it)->getUuid()) {
                  const std::string id1 = boost::lexical_cast<std::string>((*it)->getUuid());
                  const std::string id2 = boost::lexical_cast<std::string>(tempNPC->getUuid());
                  printf("NPC %s: neighbour %s\n",id1.c_str(),id2.c_str());
              }
          }
      }
  }

  client->update(dt);
  return;
}

//Geography& LocalState::getLocalMap(){
//  return *map;
//}

void LocalState::setClient(Client* c) {
  client = c;
  c->setLocalState(this);
  return;
}

Client* LocalState::getClient(){
  return client;
}

