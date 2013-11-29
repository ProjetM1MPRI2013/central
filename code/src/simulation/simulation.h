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
#include <map>
#include "miscellaneous.h"

typedef std::string EventName;

class EventListener;
#include <eventTarget.h>


/** We need a function from (target,type,listener) to callback,
 *  We create three maps : target -> (type -> (listener -> callback))
 */
template <typename RefE> using ref = std::reference_wrapper<RefE>;
typedef std::map<ref<EventListener>, std::function<void ()>, IdCarrierCmp> listenerMap;
typedef std::map<EventName, listenerMap> eventMap;
typedef std::map<ref<EventTarget>,eventMap, IdCarrierCmp> targetMap;
//typedef mtargetMap(mb) targetMap;

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
    void run(sf::Time dt);

    /*methode qui agit sur la matrice pour lisser la peur*/

    void lisserMatrice();

		/**
		*	@brief isInTile
		* @param npc : the npc you want to know the case he is in
		* gives the tile the npc is in			
		*/
    Tile& isInTile(NPC npc);

    /**
     * @brief setGeography
     * @param g : a reference to the data structure created by the city generator
     * Called by the city generator; locally sets the simulation geography
     */
    void setGeography(Geography& g);

    /**
     * @brief subscribe
     * @param eventT: event the listener subscribes to, for instance "isDestroyed"
     * @param target: target generating the event, for instance a building, a zone or an NPC
     * @param listener: the object inheriting from EventListener that wishes to be notified
     * @param callback: the method of listener that should be called when the event happens
     *
     * Any implementer of EventListener can listen to an event from the simulation. 
     * For every triple (EventName, EventTarget, EventListener) there can be at most one event subscription.
     * Oversubscribing will erase the previous callback.
     *
     * To subscribe to all events from an EventTarget, pass the empty EventName.
     * To subscribe to all events of type EventName, pass the empty EventTarget.
     */
    template <typename TargetT>
    void subscribe(EventName eventT, TargetT& target, EventListener& listener, std::function<void (EventName, TargetT&)> callback);

    /**
     * @brief unsubscribe
     * @param eventT: event the listener unsubscribes from, for instance "panicBegins"
     * @param target: target generating the event, for instance a building, a zone or an NPC
     * @param listener: the listener that does not wish to be notified anymore
     *
     * The EventListener won't receive that specific Event from the simulation.
     *
     * To unsubscribe from all events from an EventTarget, pass the empty EventName.
     * To unsubscribe from all events of a type, pass the empty EventTarget
     */
    template <typename TargetT>
    void unsubscribe(EventName eventT, TargetT& target, EventListener& listener);

    /**
     * @brief actionPerformed
     * @param a : the action that was performed
     * Called by the scenario, notifies the simulation that an action was performed: movement, firing, etc.
     */
    void scenarioActionPerformed(ScenarioAction a);

    /**
      * @brief

      */
    int actionTerroPerformed(Action a);


private :
  std::list<Camera*> cameras;
  std::list<Agent*> agents;
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
  void triggerEvent(EventName eventT, EventTarget& target);
  targetMap targets;

};


/* Subscribe and unsubscribe implementation in header because of the template */

template <typename TargetT>
void Simulation::subscribe(EventName event, TargetT& target, EventListener& listener, std::function<void (EventName, TargetT&)> callback) {
  /* Wrapping in a lambda to avoid type issues. The template ensures type safety. */
  /* Implementation note: we could create the lambda in the EventListener but
   * we may want to pass additional values to the callback in the future */
  auto run_callback = [&]() { callback(event,target); };
  targets[std::ref(target)][event][std::ref(listener)] = run_callback;
}

template <typename TargetT>
void Simulation::unsubscribe(EventName eventT, TargetT& target, EventListener& listener) {
  try {
    targets.at(std::ref(target)).at(eventT).erase(std::ref(listener));
  } catch (const std::out_of_range& e) {
    return;
  }
}

//#include "eventListener.h"

#endif // SIMULATION_H
