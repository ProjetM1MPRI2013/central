#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action {
 public:
  /**
   * @brief Action name
   * For exemple KillNPC or PlantBomb
   */
  std::string name;

  Action (std::string n);
  /**
   * @brief Check if the action is possible
   * 0 for no and 1 for yes.
   * This method has to be defined by each different actions.
   * The default behavior is to answer no to all request.
   */
  virtual int isActionPossible ();

  /**
   * @brief Do the action
   * Send the action to the game host.
   * This method has to be defined by each different actions.
   * The default behavior does nothing.
   */
  virtual void doAction ();

 private:
  std::string playerID;
};

#endif
