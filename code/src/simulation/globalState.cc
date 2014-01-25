#include "globalState.h"
#include "network/netEvent.h"
#include "scenario/NewMov.h"
#include "scenario/ScenarioActionList.h"
#include "scenario/HScenario.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#define DEBUG false

#include "debug.h"

/* Never used
GlobalState::GlobalState(std::string _seed, std::vector<Player*> _players)
    : Simulation(_seed, _players){
    isServer = true;
}
*/

GlobalState::GlobalState(Geography* map,int nbPlayers,int id) :
    Simulation(map, nbPlayers, id){
    isServer = true;
}


void GlobalState::setServer(Server *_server){
    server = _server;
    server->setSimulation(this);
}

void GlobalState::run(sf::Time dt){
  //int chance;
  //Adrien K. normalement ça devrait être bon.
  //If their is no enough money, remove an agent and a camera
  if (sous[0] < 0) {
      if (!this->agents.empty()){
        this->agents.pop_back();}
      if (!this->cameras.empty()){
        this->cameras.pop_back();}
    }

    //The server retrieve all the new messages from the network (of type Action), turn them into ScenarioAction, and add those ScenarioAction to the list of pending ScenarioAction
  std::vector<Action *> actionFromNetwork = server->receiveMessages<Action>();
  //TODO {denys} : add foreach loop
  for (std::vector<Action *>::iterator it = actionFromNetwork.begin(); it !=  actionFromNetwork.end(); ++it){
      (*it)->addPendingActions((HostSimulation*) this);
      std::cout << "Host : new Action from network of type " << (*it)->name << "\n";
    }
  actionFromNetwork.clear();

  //The server retrieve all the new messages from the network (of type NewMovNetwork), turn them into ScenarioAction, and add those ScenarioAction to the list of pending ScenarioAction
  std::vector<NewMovNetwork *> movFromNetwork = server->receiveMessages<NewMovNetwork>();
  //TODO {denys} : add foreach loop
  for (std::vector<NewMovNetwork *>::iterator it = movFromNetwork.begin(); it !=  movFromNetwork.end(); ++it){
       this->addAction((ScenarioAction *) new ChangeDirection((*it)->playerID,(*it)->movement,this));
       std::cout << "Host : New Movement from player : " << (*it)->playerID << " ";
       printNewMov((*it)->movement);
       std::cout << std::endl;
     }
  movFromNetwork.clear();


  //TODO {denys} : add foreach loop
  for (std::list<ScenarioAction*>::iterator it = pendingActions.begin();
        it != pendingActions.end(); ++it) {
      ScenarioAction* action = (*it);
      //The server sends the ScenarioAction to the client, so they can do them.
      //Adrien K. je ne suis pas sur que toutes les ScenarioAction doivent être envoyé chez le client.
      std::cout << "Host : applying pending Scenario Action of type " << action->name << "\n";
      server->broadcastMessage(*action,true);
      action->run();
    }
    pendingActions.clear();

    //On supprime les actions déjà traitées
    toDelete.clear();

    /*on empile les dt jusqu'à obtenir plus d'une seconde*/
    smallTime = smallTime + dt.asSeconds();

    /*on compte le nombre de secondes dans dt*/
    int secondes = floor(smallTime);
    smallTime = smallTime - secondes;

      /*on n'effectue pas le lissage de la matrice plus d'une fois par seconde*/
      /*  for (int i = 1; i < secondes; i++) {
        this->lisserMatrice();
        }*/

      /* We update the position of all the players */
      for (Player& player : players) { player.updatePosition(dt); }

    /*on fait payer l'entretien des différents trucs*/
  for (int i = 1; i < secondes; i++) {
    //TODO {denys} : add foreach loop
    for (std::list<Agent*>::iterator it = agents.begin();
         it != agents.end(); ++it) {
      sous[0] = sous[0] - (*it)->getEntretien();
    }
    //TODO {denys} : add foreach loop
    for (std::list<Camera*>::iterator it = cameras.begin();
       it != cameras.end(); ++it) {
     sous[0] = sous[0] - (*it)->getEntretien();
      }
  }

  //Deplacement de tous les NPCs.
  //TODO {denys} : add foreach loop
  for (std::list<NPC *>::iterator it = NPCs.begin(); it != NPCs.end(); ++it) {
      bool wasArrived = (*it)->hasArrived();
      Tile& tileBefore = (*it)->getPosition().isInTile(*map);
      (*it)->updatePosition(dt, *map);
      Tile& tileAfter = (*it)->getPosition().isInTile(*map);
      if (!tileBefore.equals(tileAfter)) {
        tileBefore.removeNPC(*it);
        tileAfter.addNPC(*it);
      }
      // Juste un test pour le EventManager (activer debug dans HScenario.cc pour le voir)
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
  server->update(dt);
  return;
}
