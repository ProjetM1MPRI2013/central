#ifndef SCENARIOACTION_H
#define SCENARIOACTION_H

class Simulation; // Forward declaration
#include <string>

/**
 * @brief An elementary action.
 * Implement a method run to performed the action.
 * This method will be called by to simulation.
 */
class ScenarioAction {
 public :

  ScenarioAction (std::string n, Simulation* s);

  /**
   * @brief The time when the action was performed.
   */
  long date;

  /**
   * @brief The name of the action
   * For exemple Explosion, ChangeDirection ...
   */
  std::string name;

  /**
   * @brief This method performed the action.
   */
  virtual void run ();

  Simulation* simulation;
} ;


#endif
