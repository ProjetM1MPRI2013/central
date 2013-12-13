#ifndef SCENARIOACTION_H
#define SCENARIOACTION_H

class Simulation; // Forward declaration
#include <string>
#include "network/abstractMessage.h"

/**
 * @brief An elementary action.
 * Implement a method run to performed the action.
 * This method will be called by to simulation.
 */
class ScenarioAction : public AbstractMessage {
 public :

  ScenarioAction (std::string n, Simulation* s);
  ScenarioAction(const ScenarioAction&);

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

  //AbstractMessage functions
  static std::string getMsgType();
  virtual std::string & toString();
  static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();
};


#endif
