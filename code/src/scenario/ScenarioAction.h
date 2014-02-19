/**
   @author: Adrien K.
 */


#ifndef SCENARIOACTION_H
#define SCENARIOACTION_H

class Simulation; // Forward declaration
#include <string>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include "network/abstractMessage.h"

/**
 * @brief An elementary action.
 * Implement a method run to performed the action.
 * This method will be called by to simulation.
 */
class ScenarioAction : public AbstractMessage {
 public :

  ScenarioAction (std::string n,int playerID, Simulation* s);
  ScenarioAction (std::string n, Simulation* s); /*for the mayor*/
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


  /**
   * @brief A ScenarioAction can be called by the Client and the Host.
   */

  Simulation* simulation;
  /**
     * @brief ID of the player who did the action.
     */
   int playerID;

  //AbstractMessage functions
  virtual AbstractMessage* copy();

protected :
  //Serialization
  ScenarioAction() ;

  SIMPLE_MESSAGE(ScenarioAction, AbstractMessage, date, name,playerID)
};



#endif
