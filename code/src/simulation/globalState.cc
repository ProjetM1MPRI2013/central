/**
  *@author Denys KANUNIKOV,
  */
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
    Simulation(map, nbPlayers, id),
    server(NULL){
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

  for (Action * action : actionFromNetwork){
      action->addPendingActions(this);
      std::cout << "Host : new Action from network of type " << action->name << "\n";
    }
  actionFromNetwork.clear();

  //The server retrieve all the new messages from the network (of type NewMovNetwork), turn them into ScenarioAction, and add those ScenarioAction to the list of pending ScenarioAction
  std::vector<NewMovNetwork *> movFromNetwork = server->receiveMessages<NewMovNetwork>();

  for (NewMovNetwork * newMove : movFromNetwork){
    this->addAction((ScenarioAction *) new ChangeDirection(newMove->playerID,newMove->newDirection,newMove->timeStamp,this));
    std::cout << "Host : New Movement from player : " << newMove->playerID ;
    std::cout << std::endl;
  }
  movFromNetwork.clear();

    for (ScenarioAction* action : pendingActions) {
      //The server sends the ScenarioAction to the client, so they can do them.
      //Adrien K. je ne suis pas sur que toutes les ScenarioAction doivent être envoyé chez le client.
      std::cout << "Host : applying pending Scenario Action of type " << action->name << "\n";
      if (action->name != "ChangeDirection"){
	std::cout << "Host : sending the action to the network\n";
	server->broadcastMessage(*action,true);
      }
      std::cout << "Nobody : serveur run action \n";
      action->run();
      std::cout << " Nobody :serveur fin run action\n";

    }
    pendingActions.clear();

    //On supprime les actions déjà traitées
    toDelete.clear();

    /*on empile les dt jusqu'à obtenir plus d'une seconde*/
    smallTime = smallTime + dt.asSeconds();

    /*on compte le nombre de secondes dans dt*/
    int secondes = floor(smallTime);
    smallTime = smallTime - secondes;

    DBG << "on lisse la matrice ";
      /*on n'effectue pas le lissage de la matrice plus d'une fois par seconde*/
      for (int i = 0; i < secondes; i++) {
        this->lisserMatrice();
        }

      /* We update the position of all the players */
      for (Player& player : players) { player.updatePosition(dt,*map); }

    /*on fait payer l'entretien des différents trucs*/
  for (int i = 1; i < secondes; i++) {
    for (Agent* agent : agents) {
      sous[0] = sous[0] - agent->getEntretien();
    }

    for (auto camera : cameras) {
     sous[0] = sous[0] - camera->getEntretien();
      }
  }

  //Deplacement de tous les NPCs.
  DBG << "on commence à bouger les npcs";
  for (NPC* npc : NPCs) {
      bool wasArrived = npc->hasArrived();
      Tile& tileBefore = npc->getPosition().isInTile(*map);
      npc->updatePosition(dt, *map);
      Tile& tileAfter = npc->getPosition().isInTile(*map);
      if (!tileBefore.equals(tileAfter)) {

        /*
         * To listen with class C, derive EventListener<C> and then:
         *
         *   listen("NPC::changedTile",someNPC,&C::someMethod);
         *
         *   with someNPC a reference to the actual stored NPC
         *   and someMethod(NPC& npc, std::pair<Tile,Tile> tilePair)
         *   tilePair.first will be tileBefore
         *   tilePair.second will be tileAfter
         *
         * To stop listening later:
         *
         *   unlisten("NPC::changedTile",someNPC);
         */
        npc->trigger("NPC::changedTile",std::pair<Tile,Tile>(tileBefore,tileAfter));
        tileBefore.removeNPC(npc);
        tileAfter.addNPC(npc);
      }
      // Juste un test pour le EventManager (activer debug dans HScenario.cc pour le voir)
      if (npc->hasArrived() or !wasArrived) {
        (*npc).trigger("NPC::arrived");
        std::cout << "suppression d'un NPC" << std::endl;
        this->supprimerNPC(npc);

      }
      if (DEBUG) {
        std::list<NPC*> neighbours = (npc)->getPosition().isInTile(*map).getNotTooFarNPCs(*map);
        while (!neighbours.empty()) {
          NPC* tempNPC = neighbours.front();
          neighbours.pop_front();
          if (tempNPC->getUuid()!= (npc)->getUuid()) {
            const std::string id1 = boost::lexical_cast<std::string>(npc->getUuid());
            const std::string id2 = boost::lexical_cast<std::string>(tempNPC->getUuid());
            printf("NPC %s: neighbour %s\n",id1.c_str(),id2.c_str());
          }
        }
      }
  }

  for(Player& player : players)
    DBG << "GlobalState : Position of player " << player.getID() << " : " << player.getPosition() ;

  server->update(dt);
  return;
}

Server* GlobalState::getServer(void){
    return server;
}
