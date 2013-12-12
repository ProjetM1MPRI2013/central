#ifndef STUFF_H
#define STUFF_H

#include <list>
#include <string>
#include "Clickable.h"
#include "Action.h"
#include "Actions.h"

class Stuff {
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
  std::list<Actions> getActionsPossible ();


  /**
   * @brief Host Stuff constructor.
   *  The host HAS TO USED this constructor. Generates a new unique identifier.
   */
  Stuff (std::string n);


  /**
   * @brief Client Stuff constructor.
   * @param id: the unique identifier of the Stuff.
   * The client HAS TO USED this constructor, with an identifier given by the server.
   */
  Stuff (std::string n, int id);

 protected:
  /**
   * @brief The list of all actions possible on the object.
   */
  std::list<Actions> actionsPossible;

 private:
  /**
   * @brief A counter used to generate unique stuffID
   */
  static int counter;
};

#endif
