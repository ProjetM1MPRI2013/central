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
  void setServer(Server*);

  /**
   * @brief Set the Client object
   */
  void setClient(Client*);

  /**
   * @brief Get a player by is playerID;
   */
  Player* getPlayerByID (int playerID);

  /**
   * @brief Get the player of this simulation
   */
  Player* getPlayer ();

	//crée un nouveau npc et l'ajoute dans une case
	void ajouterNPC(int i,int j);

	//parcourt la matrice et crée/supprime des NPCs aléatoirement en fonction de la population
	void peopleGeneration();

	Simulation(int MAP_SIZE,int TILE_SIZE_X,int TILE_SIZE_Y,int NB_JOUEURS,int id, Geography* map);

 	 /**
     * @brief run
     * @param dt: short lapse of time
     * Update all the parameters of Simulation
    */
    void run(sf::Time dt);

    /*methode qui agit sur la matrice pour lisser la peur*/

    void lisserMatrice();

		/**
		*	@brief isInTile
		* @param npc : the npc you want to know the case he is in
		* gives the tile the npc is in			
		*/
    int isInTileX(NPC* npc);

    int isInTileY(NPC* npc);

    /**
     * @brief setGeography
     * @param g : a reference to the data structure created by the city generator
     * Called by the city generator; locally sets the simulation geography
     */
    void setGeography(Geography* g);


    /**
     * @brief actionPerformed
     * @param a : the action that was performed
     * Called by the scenario, notifies the simulation that an action was performed: movement, firing, etc.
     */
    void scenarioActionPerformed(ScenarioAction a);

    //Cette fonction ne devrait pas exister [Adrien K.]
    ///**
    //  * @brief
    //
    // */
    //int actionTerroPerformed(Action a);
    int getSous();
    void enleveSous(int n);

    void supprimerNPC(NPC *);

    void supprimerNPCDansCase(int i,int j);

    void addAction(ScenarioAction * action);

    void addAgent(Agent* agent);
    void addCam(Camera* camera);

    Geography* getMap(){return map;}

private :
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
