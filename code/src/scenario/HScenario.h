#ifndef HSCENARIO_H
#define HSCENARIO_H


#include "../simulation/simulation.h"
#include "Action.h"
#include "ActionsTerro.h"
#include "ActionsPC.h"
#include "ScenarioAction.h"

//Quickfix
//Replace with includes
class EventType ;
class EventTarget ;


/**
 * @brief The host Scenario class
 * Asynchronous communications with the host Simulation class and the Network class.
 * Implement the eventListener interface.
 */
class HScenario {
  
 public :
  
  HScenario (Simulation* s);
  
  /**
   * @brief the run function called by Simulation at each iteration.
   */
  void run () ;
  
  /**
   * @brief a event has been triggered
   * @param e: event the listener subscribes to, for instance "isDestroyed"
   * @param t: target generating the event, for instance a building, a zone or an NPC
   */
  void eventTriggered (EventType e, EventTarget& t) ;
  
 private :
  Simulation* simulation;
}

#endif
