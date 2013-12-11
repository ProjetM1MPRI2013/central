#ifndef SIMULATION_H
#define SIMULATION_H
class Action;
class Player;
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


/**
 * @brief The Simulation class
 * updates the local state using its own internal rules and the actions provided by the scenario
 * provides events to subscribers
 */

class Simulation {

public :

  /**
   * @brief Set the Server object
   */
  virtual void setServer(Server*);

  /**
   * @brief Set the Client object
   */
  virtual void setClient(Client*);

  /**
   * @brief Get a player by is playerID;
   */
  virtual Player* getPlayerByID (int playerID);

  /**
   * @brief Get the player of this simulation
   */
  virtual Player* getPlayer ();

	//crée un nouveau npc et l'ajoute dans une case
	void ajouterNPC(int i,int j);

	//parcourt la matrice et crée/supprime des NPCs aléatoirement en fonction de la population
	void peopleGeneration();

	Simulation(int MAP_SIZE,int TILE_SIZE_X,int TILE_SIZE_Y,int NB_JOUEURS,int id, Geography* map);

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
		*	@brief isInTile
		* @param npc : the npc you want to know the case he is in
		* gives the tile the npc is in			
		*/
    virtual int isInTileX(NPC* npc);

    virtual int isInTileY(NPC* npc);

    /**
     * @brief setGeography
     * @param g : a reference to the data structure created by the city generator
     * Called by the city generator; locally sets the simulation geography
     */
    virtual void setGeography(Geography* g);


    /**
     * @brief actionPerformed
     * @param a : the action that was performed
     * Called by the scenario, notifies the simulation that an action was performed: movement, firing, etc.
     */
    virtual void scenarioActionPerformed(ScenarioAction a);

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

    virtual void addAction(ScenarioAction * action);

    virtual void addAgent(Agent* agent);
    virtual void addCam(Camera* camera);

    virtual Geography* getMap(){return map;}

protected :
  std::list<Camera*> cameras;
  std::list<Agent*> agents;
  Client* client;
  Server* server;
  bool isServer;
  int MAP_SIZE;
  int TILE_SIZE_X;
  int TILE_SIZE_Y;
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

};
//#include "eventListener.h"

#endif // SIMULATION_H
