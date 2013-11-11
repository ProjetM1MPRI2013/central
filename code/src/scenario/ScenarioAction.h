#IFNDEF SCENARIOACTION_H
#DEFINE SCENARIOACION_H


/**
 * All the elementary actions that the scenario can use. Each action implements a method run that performed an action.
 */

/**
 * @brief An elementary action.
 * Implement a method run to performed the action.
 */
class ScenarioAction {
 public :
  Simulation simulation;

  /**
   * @brief This method performed the action.
   */
  static void run () {}
}


#ENDIF
