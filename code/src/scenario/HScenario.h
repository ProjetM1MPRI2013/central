/**
   @author: Adrien K.
 */


#ifndef HSCENARIO_H
#define HSCENARIO_H

class Simulation;
#include "Action.h"
#include "ActionsTerro.h"
#include "ActionsPC.h"
#include "ScenarioAction.h"

/**
 * @brief The host Scenario class
 * Asynchronous communications with the host Simulation class and the Network class.
 * Implement the eventListener interface.
 */
class HScenario : public EventListener<HScenario> {
  
 public :
  
  HScenario (Simulation& s);
  
  /**
   * @brief the run function called by Simulation at each iteration.
   */
  void run () ;
  
  void createdNPC(Simulation& s, NPC& npc);
  void arrivedNPC(NPC& npc);

  Simulation& simulation;
};

#endif
