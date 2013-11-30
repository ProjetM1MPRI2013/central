#ifndef SCENARIOACTION_H
#define SCENARIOACTION_H

#include "../simulation/simulation.h"
class Simulation; // Forward declaration
#include <string>

/**
 * @brief An elementary action.
 * Implement a method run to performed the action.
 * This method will be called by to simulation.
 */
class ScenarioAction {
 public :

  static void setSimulation(Simulation* s);

  ScenarioAction (std::string n);

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

 private:
  static Simulation* simulation;
} ;


#endif
