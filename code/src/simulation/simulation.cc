#include <math.h>
#include "simulation.h"
#include "../generation/geography.h"
#include "../generation/tile.h"
#include "npc.h"
#include <cstdlib>
#include <iostream>
#include "position.h"
#include "generation/generation1.h"
#include "network/netEvent.h"
#include "scenario/NewMov.h"
#include "scenario/ScenarioActionList.h"
#include "scenario/HScenario.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#define DEBUG false

#define DEBUG true
#include "debug.h"

Simulation::Simulation(int nbPlayers, int id)
{
	this->NB_JOUEURS = nbPlayers;
        //[joseph]map n'est pas définie donc ce qui suit est juste map = map
        //this->map = map;
	//this->oldMap = map;
	this->Id = id;

	int t[NB_JOUEURS];
	for (int i = 0; i < NB_JOUEURS; i++) {
		t[i] = 0;
	}
	this->mesSous = 0;
	this->sous = t;
	this->relativeTime = 0;
	this->absoluteTime = 0;
	this->smallTime = 0;
	
	this->players.push_back(new Player(id,0,0));

	std::list<NPC*> NPCs;
	this->NPCs = NPCs;
}

Simulation::Simulation(Geography* map, int nbPlayers, int id) : Simulation(nbPlayers, id) {
  this->setGeography(map);
}

Simulation::Simulation(std::string seed, std::vector<Player *> p_vect) : Simulation(p_vect.size(),0) {
  this->setGeography(new Generation1(seed));
  for(Player* p : p_vect)
    this->players.push_back(p);
}

void Simulation::setServer(Server* s) {
  this->isServer = true;
  this->server = s;
  return;
}
;

void Simulation::setClient(Client* c) {
  this->isServer = false;
  this->client = c;
  
  //Ceci ne marche pas, il faudrait que setData prenne un data en entré, et non pas un data*
  //NetEvent e ;
  //e.setType(NetEvent::PLAYER_JOIN);
  //e.setData(&this->getPlayer()->getID());
  //cli->sendMessage(e);

  return;
}
;

bool Simulation::simIsServer(){
  return this->isServer;
}

Client* Simulation::getClient(){
  return this->client;
}

void Simulation::addPlayer(Player* p){
  this->players.push_back(p);
  return;
}

void Simulation::addAction(ScenarioAction * action) {
  this->pendingActions.push_back(action);
}

Player* Simulation::getPlayerByID(int pid) {
  Player* result = 0;
  for (std::list<Player*>::iterator it = players.begin(); it != players.end();
       ++it) {
    if ((*it)->getID() == pid) {
      result = *it;
    };
  };
  if (result == 0) {
    std::cerr << "getPlayerByID error : Unknown playerID " << pid << std::endl;
  };
  return result;
}


Player* Simulation::getPlayer() {
  return this->getPlayerByID(this->Id);
}


void Simulation::deleteAction(Action* a){
  this->toDelete.push_back(a);
  return;
}


//Simplement des casts en float de pow, sqrt et floor
float pow2(float x, float y) {
  return ((float) (pow((double(x)), double(y))));
}


float sqrt2(float x) {
  return ((float) (sqrt((double) x)));
}


float floor2(float x) {
  return ((float) (floor((double(x)))));
}

void Simulation::addNPC(Position start, Position target, float speed, TexturePack* tex) {
  //on crée le NPC
  NPC *npc = new NPC(speed, 10, 10, start, target, *map, tex);
  //on l'ajoute à la liste
  NPCs.push_front(npc);
  //on le met dans sa tile de départ
  start.isInTile(*map).addNPC(npc);

  trigger("NPC::created",*npc);
  return;
}


void Simulation::supprimerNPC(NPC * npc) {
  //on le retire de sa tile
  npc->getPosition().isInTile(*map).removeNPC(npc);
  //on le retire de la liste
  NPCs.remove(npc);
  //on le supprime
  delete npc;
  return;
}


void Simulation::supprimerNPCDansCase(int i, int j) {
  //on récupère le 1er NPC de la tile
  NPC *npc = map->getTileRef(i,j).getNPCs().front();
  //on le supprime de la tile
  map->getTileRef(i,j).removeNPC(npc);
  //on le supprime de la liste
  NPCs.remove(npc);
  return;
}


//Crée et tue les gens dans les cases
void Simulation::peopleGeneration() {
  float chance;
  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      chance = (rand() % 100);
      if (chance > (map->getTile(i, j)->getPopulationDensity() / 10)) {
        //[joseph]nope
        //il faut aussi vérifier qu'il ne spawn pas dans une maison
        //ajouterNPC(i, j,rand()/MAP_SIZE,rand()/MAP_SIZE,NULL);
      }
      if (chance < (map->getTile(i, j)->getPopulationDensity() / 10)) {
        supprimerNPCDansCase(i, j);
      }
    }
  }
  return;
}


//Nivelle la peur via une sorte de norme 2
void Simulation::lisserMatrice() {
  float anxiety;
  float population;
  //Adrien K. : Heuuuuu, ..... je trouve cette ligne bizarre ...
  *oldMap = *map;
  //interieur de la map
  for (int i = 1; i < MAP_SIZE - 2; i++) {
    for (int j = 1; i < MAP_SIZE - 2; j++) {
      //calcul
      anxiety =
        sqrt2(
              (1 / 8)
              * (2 * pow2(oldMap->getAnxiety(i, j), 2)
                 + pow2(oldMap->getAnxiety(i - 1, j),
                        2)
                 + pow2(oldMap->getAnxiety(i, j - 1),
                        2)
                 + pow2(oldMap->getAnxiety(i + 1, j),
                        2)
                 + pow2(oldMap->getAnxiety(i, j + 1),
                        2)
                 + (1 / 2)
                 * (pow2(
                         oldMap->getAnxiety(
                                            i - 1,
                                            j + 1), 2)
                    + pow2(
                           oldMap->getAnxiety(
                                              i
                                              + 1,
                                              j
                                              + 1),
                           2)
                    + pow2(
                           oldMap->getAnxiety(
                                              i
                                              - 1,
                                              j
                                              - 1),
                           2)
                    + pow2(
                           oldMap->getAnxiety(
                                              i
                                              + 1,
                                              j
                                              - 1),
                           2))));
      //set
      map->setAnxiety(i, j, anxiety);
    }
  }

  //bande en bas (i=0)
  for (int j = 1; j < MAP_SIZE - 2; j++) {
    //calcul
    anxiety = sqrt2(
                    (1 / 6)
                    * (2 * pow2(oldMap->getAnxiety(0, j), 2)
                       + pow2(oldMap->getAnxiety(0, j - 1), 2)
                       + pow2(oldMap->getAnxiety(1, j), 2)
                       + pow2(oldMap->getAnxiety(0, j + 1), 2)
                       + (1 / 2)
                       * (pow2(oldMap->getAnxiety(1, j + 1), 2)
                          + pow2(
                                 oldMap->getAnxiety(1,
                                                    j - 1), 2))));
    //set
    map->setAnxiety(0, j, anxiety);
  }

  //bande à gauche (j=0)
  for (int i = 1; i < MAP_SIZE - 2; i++) {
    //calcul
    anxiety = sqrt2(
                    (1 / 6)
                    * (2 * pow2(oldMap->getAnxiety(i, 0), 2)
                       + pow2(oldMap->getAnxiety(i - 1, 0), 2)
                       + pow2(oldMap->getAnxiety(i + 1, 0), 2)
                       + pow2(oldMap->getAnxiety(i, 0 + 1), 2)
                       + (1 / 2)
                       * (pow2(
                               oldMap->getAnxiety(i - 1,
                                                  0 + 1), 2)
                          + pow2(
                                 oldMap->getAnxiety(
                                                    i + 1, 0 + 1),
                                 2))));
    //set
    map->setAnxiety(i, 0, anxiety);
  }

  //bande à droite (j=MAP_SIZE -1)
  for (int i = 1; i < MAP_SIZE - 2; i++) {
    //calcul
    anxiety =
      sqrt2(
            (1 / 6)
            * (2
               * pow2(
                      oldMap->getAnxiety(i,
                                         MAP_SIZE - 1), 2)
               + pow2(
                      oldMap->getAnxiety(i - 1,
                                         MAP_SIZE - 1), 2)
               + pow2(
                      oldMap->getAnxiety(i + 1,
                                         MAP_SIZE - 1), 2)
               + pow2(
                      oldMap->getAnxiety(i,
                                         MAP_SIZE - 1 - 1), 2)
               + (1 / 2)
               * (pow2(
                       oldMap->getAnxiety(
                                          i - 1,
                                          MAP_SIZE - 1
                                          - 1), 2)
                  + pow2(
                         oldMap->getAnxiety(
                                            i + 1,
                                            MAP_SIZE
                                            - 1
                                            - 1),
                         2))));
    //set
    map->setAnxiety(i, MAP_SIZE - 1, anxiety);
  }

  //bande en haut (i=MAP_SIZE -1)
  for (int j = 1; j < MAP_SIZE - 2; j++) {
    //calcul
    anxiety = sqrt2(
                    (1 / 6)
                    * (2 * pow2(oldMap->getAnxiety(MAP_SIZE - 1, j), 2)
                       + pow2(oldMap->getAnxiety(MAP_SIZE - 2, j), 2)
                       + pow2(oldMap->getAnxiety(MAP_SIZE - 1, j - 1),
                              2)
                       + pow2(oldMap->getAnxiety(MAP_SIZE - 1, j + 1),
                              2)
                       + (1 / 2)
                       * (pow2(
                               oldMap->getAnxiety(MAP_SIZE - 2,
                                                  j + 1), 2)
                          + pow2(
                                 oldMap->getAnxiety(
                                                    MAP_SIZE - 2,
                                                    j - 1), 2))));
    //set
    map->setAnxiety(MAP_SIZE - 1, j, anxiety);
  }

  //coin en haut à gauche
  anxiety = sqrt2(
                  (1 / 4.5)
                  * (2 * pow2(oldMap->getAnxiety(0, MAP_SIZE - 1), 2)
                     + pow2(oldMap->getAnxiety(0, MAP_SIZE - 2), 2)
                     + pow2(oldMap->getAnxiety(1, MAP_SIZE - 1), 2)
                     + (1 / 2)
                     * (pow2(oldMap->getAnxiety(1, MAP_SIZE - 2),
                             2))));
  map->setAnxiety(0, MAP_SIZE - 1, anxiety);

  //coin en haut à droite
  anxiety = sqrt2(
                  (1 / 4.5)
                  * (2
                     * pow2(
                            oldMap->getAnxiety(MAP_SIZE - 1,
                                               MAP_SIZE - 1), 2)
                     + pow2(
                            oldMap->getAnxiety(MAP_SIZE - 1,
                                               MAP_SIZE - 2), 2)
                     + pow2(
                            oldMap->getAnxiety(MAP_SIZE - 2,
                                               MAP_SIZE - 1), 2)
                     + (1 / 2)
                     * (pow2(
                             oldMap->getAnxiety(MAP_SIZE - 2,
                                                MAP_SIZE - 2), 2))));
  map->setAnxiety(MAP_SIZE - 1, MAP_SIZE - 1, anxiety);

  //coin en bas à gauche
  anxiety = sqrt2(
                  (1 / 4.5)
                  * (2 * pow2(oldMap->getAnxiety(0, 0), 2)
                     + pow2(oldMap->getAnxiety(0, 1), 2)
                     + pow2(oldMap->getAnxiety(1, 0), 2)
                     + (1 / 2) * (pow2(oldMap->getAnxiety(1, 1), 2))));
  map->setAnxiety(0, 0, anxiety);

  //coin en bas à droite
  anxiety = sqrt2(
                  (1 / 4.5)
                  * (2 * pow2(oldMap->getAnxiety(MAP_SIZE - 1, 0), 2)
                     + pow2(oldMap->getAnxiety(MAP_SIZE - 1, 1), 2)
                     + pow2(oldMap->getAnxiety(MAP_SIZE - 2, 0), 2)
                     + (1 / 2)
                     * (pow2(oldMap->getAnxiety(MAP_SIZE - 2, 1),
                             2))));
  map->setAnxiety(MAP_SIZE - 1, 0, anxiety);

  return;
}


void Simulation::run(sf::Time dt) {
  int chance;
  //Adrien K. normalement ça devrait être bon.
  //If their is no enough money, remove an agent and a camera
  if (sous[0] < 0) {
    if (!this->agents.empty()){
      this->agents.pop_back();}
    if (!this->cameras.empty()){
      this->cameras.pop_back();}
  }


  //The server retrieve all the new messages from the network (of type Action), turn them into ScenarioAction, and add those ScenarioAction to the list of pending ScenarioAction
  if (this->isServer){
    std::vector<Action *> actionFromNetwork = this->server->receiveMessages<Action>();
    for (std::vector<Action *>::iterator it = actionFromNetwork.begin(); it !=  actionFromNetwork.end(); ++it){
      (*it)->addPendingActions((HostSimulation*) this);
      std::cout << "Host : new Action from network of type " << (*it)->name << "\n";
    }
    actionFromNetwork.clear();
  }

 //The server retrieve all the new messages from the network (of type NewMovNetwork), turn them into ScenarioAction, and add those ScenarioAction to the list of pending ScenarioAction
  if (this->isServer){
    std::vector<NewMovNetwork *> movFromNetwork = this->server->receiveMessages<NewMovNetwork>();
    for (std::vector<NewMovNetwork *>::iterator it = movFromNetwork.begin(); it !=  movFromNetwork.end(); ++it){
      this->addAction((ScenarioAction *) new ChangeDirection((*it)->playerID,(*it)->movement,this));
      
      std::cout << "Host : New Movement from player : " << (*it)->playerID << " ";
      printNewMov((*it)->movement);
      std::cout << std::endl;
      
    }
    movFromNetwork.clear();
  }

  //The client retrieve all the new messages from the network (of type ScenarioAction), and add them to the list of pending ScenarioAction
  if (!this->isServer){
    std::vector<ScenarioAction *> scenarioActionFromNetwork = this->client->receiveMessages<ScenarioAction>();
    for (std::vector<ScenarioAction *>::iterator it = scenarioActionFromNetwork.begin(); it !=  scenarioActionFromNetwork.end(); ++it){
      std::cout << "Client : add a ScenarioAction from network of type " << (*it)->name << "\n";
      (*it)->simulation = this;
      this->addAction(*it);
    }
  }
  
  for (std::list<ScenarioAction*>::iterator it = pendingActions.begin();
       it != pendingActions.end(); ++it) {
    ScenarioAction* action = (*it);
    //The server sends the ScenarioAction to the client, so they can do them.
    if (this->isServer){
      //Adrien K. je ne suis pas sur que toutes les ScenarioAction doivent être envoyé chez le client.
      std::cout << "Host : applying pending Scenario Action of type " << action->name << "\n";
      this->server->broadcastMessage(*action,true);
    } else {
      std::cout << "Client : applying pending Scenario Action of type " << action->name << "\n";
    }
    action->run();
  }
  this->pendingActions.clear();

  //On supprime les actions déjà traitées
  this->toDelete.clear();

  /*on empile les dt jusqu'à obtenir plus d'une seconde*/
  this->smallTime = smallTime + dt.asSeconds();

  /*on compte le nombre de secondes dans dt*/
  int secondes = floor2(smallTime);
  smallTime = smallTime - secondes;

  /*on n'effectue pas le lissage de la matrice plus d'une fois par seconde*/
  /*  for (int i = 1; i < secondes; i++) {
    this->lisserMatrice();
    }*/

  /* We update the position of all the players */
  for (std::list<Player*>::iterator it = players.begin(); it != players.end();
       ++it) {
    (*it)->updatePosition(dt);
  }

  /*on fait payer l'entretien des différents trucs*/
  for (int i = 1; i < secondes; i++) {
    for (std::list<Agent*>::iterator it = agents.begin();
         it != agents.end(); ++it) {
      this->sous[0] = this->sous[0] - (*it)->getEntretien();
    }

    for (std::list<Camera*>::iterator it = cameras.begin();
         it != cameras.end(); ++it) {
      this->sous[0] = this->sous[0] - (*it)->getEntretien();
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

  return;
}


int Simulation::getSous() {
  return (this->sous[0]);
}


void Simulation::enleveSous(int n) {
  this->sous[0] = this->sous[0] - n;
  return;
}


void Simulation::addAgent(Agent* agent) {
  agents.push_back(agent);
  return;
}


void Simulation::addCam(Camera* cam) {
  cameras.push_back(cam);
  return;
}


void Simulation::setGeography(Geography *g){
  this->map = g ;
  if (g) {
    this->MAP_SIZE = map->getMapWidth();
  }
  return;
}


void Simulation::setScenario(HScenario* s) {
  scenario = s;
  return;
}
