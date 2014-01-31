/**
   @author: Adrien K.
 */


#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <time.h>
#include <cerrno>
#include <iostream>
class Player;
class Simulation;
#include "simulation/simulation.h"
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
  Action (const Action&);

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
  
  // AbstractMessage function
  virtual AbstractMessage* copy();


 protected:
  Simulation* simulation;
  
 private:
  int playerID;

protected :
  //Serialization

  /**
   * @brief Action : Default constructor used for serialization
   */
  Action() ;

  SIMPLE_MESSAGE(Action, AbstractMessage)

};

BOOST_CLASS_EXPORT_KEY(Action)

#endif
