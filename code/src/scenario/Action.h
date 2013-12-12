#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <time.h>
#include <cerrno>
#include <iostream>
class Player;
class Simulation;
#include "../simulation/simulation.h"
#include "network/abstractMessage.h"

typedef Simulation HostSimulation;

class Action : public AbstractMessage {
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

  /**
   * @brief Add pending actions
   * This method convert theaction to a list of ScenarioAction and add the to the host simulation scenario action pending list.
   */
  virtual void addPendingActions(HostSimulation* hs);
  

  //AbstractMessage functions
  static std::string getMsgType();
  virtual std::string & toString();
  static AbstractMessage* fromString(std::string& msg);
  virtual AbstractMessage* copy();


 protected:
  Simulation* simulation;
  
 private:
  int playerID;
};

#endif
