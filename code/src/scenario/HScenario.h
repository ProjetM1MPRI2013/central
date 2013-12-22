#ifndef HSCENARIO_H
#define HSCENARIO_H

class Simulation;
#include "Action.h"
#include "ActionsTerro.h"
#include "ActionsPC.h"
#include "ScenarioAction.h"



//Quickfix
//Replace with includes
class EventTarget ;


/**
 * @brief The host Scenario class
 * Asynchronous communications with the host Simulation class and the Network class.
 * Implement the eventListener interface.
 */
class HScenario : public EventListener {
  
 public :
  
  HScenario (Simulation& s);
  
  /**
   * @brief the run function called by Simulation at each iteration.
   */
  void run () ;
  
  /**
   * @brief a event has been triggered
   * @param e: event the listener subscribes to, for instance "isDestroyed"
   * @param t: target generating the event, for instance a building, a zone or an NPC
   */
  void eventTriggered (EventName e, EventTarget& t) ;
  void createdNPC(EventName e, Simulation& s, NPC& npc);
  void arrivedNPC(EventName e, NPC& npc);

  Simulation& simulation;
};

#endif
