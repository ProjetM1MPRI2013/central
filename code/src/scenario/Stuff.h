/**
   @author: Adrien K,Rémy P.
 */


#ifndef Clickable_H
#define Clickable_H

#include <list>
#include <string>
#include "Actions.h"
#include "PreStuff.h"
#include "network/abstractMessage.h"
#include "drawableObject.h"

class Clickable : public AbstractMessage, public DrawableObject{
public :
	/**
   * @brief The Clickable name
   * For exemple Knife or Bomb ...
   */
  std::string name;
  /**
   * @brief The ID of the object
   * An unique integer identifying the object on the client.
   */
  int ClickableID;
  /**
   * @brief Return the list of ActionType possible
   */
  std::list<ActionType> getActionTypePossible ();


  /**
   * @brief Host Stuff constructor.
   *  The host HAS TO USED this constructor. Generates a new unique identifier.
   */
  Clickable ();

  Clickable (std::string n);


  /**
   * @brief Client Stuff constructor.
   * @param id: the unique identifier of the Stuff.
   * The client HAS TO USED this constructor, with an identifier given by the server.
   */
  Clickable (std::string n, int id);

 protected:
  /**
   * @brief The list of all ActionType possible on the object.
   */
  std::list<ActionType> ActionTypePossible;

 private:
  /**
   * @brief A counter used to generate unique stuffID
   */
  static int counter;
 protected :
 //Serialization
  AbstractMessage* copy();
 SIMPLE_MESSAGE(Clickable,AbstractMessage,ClickableID,name);
};


#endif

