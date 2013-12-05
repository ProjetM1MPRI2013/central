#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <time.h>
#include <cerrno>
#include <iostream>
class Simulation;
#include "../simulation/simulation.h"

class Action {
 public:
  /**
   * @brief Action name
   * For exemple KillNPC or PlantBomb
   */
  std::string name;

  /**
   * @brief The time when the action was performed.
   */
  long date;

  /**
   * @brief Delay to do the action before executing.
   */
  long delay;

  Action (std::string n, Simulation* s);

  /**
   * @brief Check if the action is possible
   * This method has to be defined by each different actions.
   * The default behavior is to answer no to all request.
   */
  virtual bool isActionPossible ();

  /**
   * @brief Do the action
   * Send the action to the game host.
   * This method has to be defined by each different actions.
   * The default behavior does nothing.
   */
  virtual void doAction ();
  
 protected:
  Simulation* simulation;
  
 private:
  int playerID;
};

#endif
