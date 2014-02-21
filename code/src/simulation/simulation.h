/**
 *@author Denys Kanunikov, others...
 */

#ifndef SIMULATION_H
#define SIMULATION_H
class Action;
class Player;
class HScenario;
class GraphicContextIso;

#include "../scenario/Action.h"
#include "../scenario/Stuff.h"
#include "ScenarioAction.h"
#include "npc.h"
#include "SFML/System.hpp"
#include <iostream>
#include <list>
#include <set>
#include <cerrno>
#include "miscellaneous.h"
#include "eventManager.h"
#include "eventSource.h"
#include "eventListener.h"
#include "time.h"
#include "player.h"
#include "../network/network.h"
#include "../graphism/animation.h"

/**
 * @brief The Simulation class
 * updates the local state using its own internal rules and the actions provided by the scenario
 * provides events to listeners
 */

class Simulation: public EventSource {

public:
  /**
   * @brief Get a player by its playerID;
   */
  virtual Player& getPlayerByID(int playerID);

  /**
   * @brief Get the player of this simulation
   */
  virtual Player* getPlayer();

  /**
   * @brief Add a player to the player list
   */
  virtual void addPlayer(Player&& p);

  /**
   * @brief addNPC
   * creates a new NPC
   * @param start: start position
   * @param target: target position
   * @param speed: the NPC's speed in tiles/s
   * @param tex: the texturepack for the NPC
   */
  void addNPC(Position start, Position target, float speed, TexturePack* tex);

  /**
   * @brief addNPC
   * creates a new NPC
   * @param start: start position
   * @param target: target position
   * @param speed: the NPC's speed in tiles/s
   * @param tex: the texturepack for the NPC
   * @param id: id of the npc to synch
   */
  void addNPC(Position start, Position target, float speed, TexturePack* tex,
              boost::uuids::uuid id);

  /**
   * @brief peopleGeneration : parcourt la matrice et crée/supprime des NPCs
   * aléatoirement en fonction de la population
   */
  void peopleGeneration();

  Simulation(int nbPlayers,int id);
  Simulation(Geography* map,int nbPlayers,int id);
  ~Simulation();

  /**
   * @brief reroute : to recalculate the path
   * @param npc : whose path will be recalculated
   */
  void reroute(NPC& npc);

  void setContextIso(GraphicContextIso* gra);

  /*methode qui agit sur la matrice pour lisser la peur*/
  virtual void lisserMatrice();
  template <class T>

  T& getItemByID(int id);
  /**
   * @brief setGeography
   * @param g : a reference to the data structure created by the city generator
   * Called by the city generator; locally sets the simulation geography
   */
   virtual void setGeography(Geography* g);

   virtual int getSous();
   virtual void enleveSous(int n);
   virtual void supprimerNPC(NPC *);
   virtual void supprimerNPCDansCase(int i,int j);

   /**
     * @brief addAction
     * Called by the scenario, notifies the simulation that an action has to be
     * performed: movement, firing, etc.
     */
   virtual void addAction(ScenarioAction * action);
   virtual void addAgent(Agent* agent);
   virtual void addCam(Camera* camera);
   /**
     * @brief Add the action to a list, and will be deleted later
     */
   virtual void deleteAction(Action* a);

   virtual Geography* getMap() {return map;}

   virtual bool simIsServer();
   void setScenario(HScenario* s);
   /**
    * @brief Find NPC by id. 
    * @return nullptr if NPC not found, a pointer to the NPC otherwise.
    */
   NPC* getNPCByID(boost::uuids::uuid uuid);
protected :

   //Pour pouvoir créer des npcs
   GraphicContextIso* graContIso;

   void copyTmp();
   std::list<Camera*> cameras;
   std::list<Agent*> agents;

   /**
    * @brief tmp: used to copy only required information from *map to calculate
    * fear (peur)
    */
   std::vector<std::vector<int> > tmp;

   HScenario* scenario;
   bool isServer;
   int MAP_SIZE;
   const int TILE_SIZE_X = 1;
   const int TILE_SIZE_Y = 1;
   int NB_JOUEURS;
   /**
    * @brief Id
    * 0 pour le maire = le serveur, i pour le joueur i
    */
   int Id;

   std::vector<int> sous; //tableau des sous de tout le monde
   int mesSous;

   float absoluteTime;
   float relativeTime;
   float smallTime;
   Geography* map;
   std::list<Player> players;
   std::map<boost::uuids::uuid, NPC*> NPCs;
   std::list<ScenarioAction *> pendingActions;
   /**
    * @brief toDelete : liste des actions déjà traité
    */
   std::list<Action*> toDelete;
};

template<class T>
T& Simulation::getItemByID(int stuffID) {
  for (auto& player : players) {
    try {
      return player.getItemByID<T>(stuffID);
    } catch (const StuffNotFound& err) {}
  }
  throw StuffNotFound();
}

#endif // SIMULATION_H
