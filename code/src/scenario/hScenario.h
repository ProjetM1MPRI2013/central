#IFNDEF HSCENARIO_H
#DEFINE HSCENARIO_H


#include "Event.h"
#include "Action.h"
#include "ScenarioAction.h"


/**
 * @brief The host Scenario class
 * Asynchronous communications with the host Simulation class and the Network class.
 * Implement the eventListener interface.
 */
class Scenario {
  
 public :
  
  /**
   * @brief the run function called by Simulation at each iteration.
   */
  static void run () {}

  /**
   * @brief a event has been triggered
   * @param e: event the listener subscribes to, for instance "isDestroyed"
   * @param t: target generating the event, for instance a building, a zone or an NPC
   */
  static void eventTriggered (EventType e, EventTarget& t) {}
  
  /**
   * @brief new action from Network
   * @param a: action that have to be performed
   */
  static void newAction (Action a)

}

#ENDIF
