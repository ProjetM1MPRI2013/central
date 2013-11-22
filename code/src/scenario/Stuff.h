#ifndef STUFF_H
#define STUFF_H

#include <list>
#include <string>
#include "Clickable.h"
#include "Action.h"

class Stuff : public Clickable {
 public :
  /**
   * @brief The stuff name
   * For exemple Knife or Bomb ...
   */
  std::string name;

  /**
   * @brief The ID of the object
   * An unique integer identifying the object on the client.
   */
  int stuffID;

  /**
   * @brief Return the list of actions possible
   */
  virtual std::list<std::string> getActionsPossible ();

  Stuff (std::string n);

 protected:
  /**
   * @brief The list of all actions possible on the object.
   */
  std::list<std::string> actionsPossible;

 private:
  /**
   * @brief A counter used to generate unique stuffID
   */
  static int counter;
};

#endif
