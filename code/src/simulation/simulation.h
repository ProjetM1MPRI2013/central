#ifndef SIMULATION_H
#define SIMULATION_H
// no such file
//scenario/action.h ?
#include "Action.h"
#include "ScenarioAction.h"
#include "npc.h"
#include "SFML/System.hpp"
#include <iostream>
#include <list>
#include "miscellaneous.h"

class Geography ;
class EventType ;
class EventTarget ;
class EventListener ;

/**
 * @brief The Simulation class
 * updates the local state using its own internal rules and the actions provided by the scenario
 * provides events to subscribers
 */

class Simulation {

public :

 	 /**
     * @brief run
     * @param dt: short lapse of time
     * Update all the parameters of Simulation
    */
    static void run(sf::Time dt);

    /*methode qui agit sur la matrice pour lisser la peur*/

    void lisserMatrice();

		/**
		*	@brief isInTile
		* @param npc : the npc you want to know the case he is in
		* gives the tile the npc is in			
		*/
	static Tile& isInTile(NPC npc);

    /**
     * @brief setGeography
     * @param g : a reference to the data structure created by the city generator
     * Called by the city generator; locally sets the simulation geography
     */
    static void setGeography(Geography& g);

    /**
     * @brief subscribe
     * @param e: event the listener subscribes to, for instance "isDestroyed"
     * @param t: target generating the event, for instance a building, a zone or an NPC
     * @param l: the object inheriting from EventListener that wishes to be notified
     *
     * Any implementer of EventListener can listen to an event from the simulation. 
     * There can be at most one subscription for every  (EventType, EventTarget, EventListener).
     *
     * To subscribe to all events from an EventTarget, pass the empty EventType.
     * To subscribe to all events of type EventType, pass the empty EventTarget.
     */
    static void subscribe(EventType e, EventTarget& t, EventListener& l);

    /**
     * @brief unsubscribe
     * @param e: event the listener unsubscribes from, for instance "panicBegins"
     * @param t: target generating the event, for instance a building, a zone or an NPC
     * @param l: the listener that does not wish to be notified anymore
     *
     * The EventListener won't receive that specific Event from the simulation.
     *
     * To unsubscribe from all events from an EventTarget, pass the empty EventType.
     * To unsubscribe from all events of a type, pass the empty EventTarget
     */
    static void unsubscribe(EventType e, EventTarget& t, EventListener& l);

    /**
     * @brief actionPerformed
     * @param a : the action that was performed
     * Called by the scenario, notifies the simulation that an action was performed: movement, firing, etc.
     */
    static void scenarioActionPerformed(ScenarioAction a);

    /**
      * @brief

      */
    static int actionTerroPerformed(Action a);

private :
  std::list<Camera&> cameras;
  std::list<Agent&> agents;
  int sous;
  const int MAP_SIZE;
  const int TILE_SIZE_X;
  const int TILE_SIZE_Y;
  float absoluteTime;
  float relativeTime;
  float smallTime;
  Geography map;
  Geography oldMap;
  std::list<NPC> NPCs;

};


#endif // SIMULATION_H
