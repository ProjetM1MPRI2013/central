#ifndef SIMULATION_H
#define SIMULATION_H
class Action;
class Player;
class HScenario;
#include "../scenario/Action.h"
#include "../scenario/Stuff.h"
#include "ScenarioAction.h"
#include "npc.h"
#include "SFML/System.hpp"
#include <iostream>
#include <list>
#include <cerrno>
#include "miscellaneous.h"
#include "eventManager.h"
#include "eventTarget.h"
#include "eventListener.h"
#include "time.h"
#include "player.h"
#include "../network/network.h"
#include "../graphism/animation.h"

/**
 * @brief The Simulation class
 * updates the local state using its own internal rules and the actions provided by the scenario
 * provides events to subscribers
 */

class Simulation : public EventTarget {

 public :

  /**
   * @brief Set the Server object
   */
  virtual void setServer(Server*);

  /**
   * @brief Set the Client object
   */
  virtual void setClient(Client*);

  virtual Client* getClient();

  /**
   * @brief Get a player by is playerID;
   */
  virtual Player* getPlayerByID (int playerID);

  /**
   * @brief Get the player of this simulation
   */
  virtual Player* getPlayer ();


  /**
   * @brief Add a player to the player list
   */
  virtual void addPlayer(Player* p);

  /**
   * @brief addNPC
   * creates a new NPC
   * @param start: start position
   * @param target: target position
   * @param speed: the NPC's speed in tiles/s
   * @param tex: the texturepack for the NPC
   */
  void addNPC(Position start, Position target, float speed, TexturePack* tex);

  //parcourt la matrice et crée/supprime des NPCs aléatoirement en fonction de la population
  void peopleGeneration();
  
  
  Simulation(int nbPlayers,int id);
  Simulation(Geography* map,int nbPlayers,int id);
  Simulation(std::string seed, std::vector<Player*> players) ;
  
  /**
   * @brief run
   * @param dt: short lapse of time
   * Update all the parameters of Simulation
   */
  virtual void run(sf::Time dt);

  /*methode qui agit sur la matrice pour lisser la peur*/
  
  virtual void lisserMatrice();
    
  /**
   * @brief setGeography
   * @param g : a reference to the data structure created by the city generator
   * Called by the city generator; locally sets the simulation geography
   */
  virtual void setGeography(Geography* g);
  
  //Cette fonction ne devrait pas exister [Adrien K.]
  ///**
  //  * @brief
  //
  // */
  //int actionTerroPerformed(Action a);
  virtual int getSous();
  virtual void enleveSous(int n);
  
  virtual void supprimerNPC(NPC *);
  
  virtual void supprimerNPCDansCase(int i,int j);
  
    
  /**
   * @brief addAction
   * Called by the scenario, notifies the simulation that an action has to be performed: movement, firing, etc.
   */
  virtual void addAction(ScenarioAction * action);
    
  virtual void addAgent(Agent* agent);
  virtual void addCam(Camera* camera);

  /**
   * @brief Add the action to a list, and will be deleted later
   */
  virtual void deleteAction(Action* a);

  virtual Geography* getMap(){return map;}

  virtual bool simIsServer();
  void setScenario(HScenario* s);
 protected :
  std::list<Camera*> cameras;
  std::list<Agent*> agents;
  Client* client;
  Server* server;
  HScenario* scenario;
  bool isServer;
  int MAP_SIZE;
  const int TILE_SIZE_X = 1;
  const int TILE_SIZE_Y = 1;
  int NB_JOUEURS;
  int Id; //0 pour le maire = le serveur, i pour le joueur i
  int* sous; //tableau des sous de tout le monde
  int mesSous;
  float absoluteTime;
  float relativeTime;
  float smallTime;
  Geography* map;
  Geography* oldMap;
  std::list<Player*> players;
  std::list<NPC *> NPCs;
  std::list<ScenarioAction *> pendingActions;
  //liste des actions déjà traité
  std::list<Action*> toDelete;

};
//#include "eventListener.h"

#endif // SIMULATION_H
