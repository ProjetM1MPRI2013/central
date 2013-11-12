#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <string>

class Action ;
//Should be declared somewhere else
class ActionType {
public :
    ActionType(std::string & s){}
} ;


/**
 * @brief StuffType.
 * there is 3 type of Stuff : object, character and internet.
 * an exemple of subtype is explosive.
 */

class Stuff {
 public :
  std::string name;
  std::string type;
/**
 * @brief actionPossible.
 * A vector of type of action possible with this stuff.
 */
  //If you want to use fixed size array,
  //precise its size in declaration
  std::vector<Action> actionPossible;
  //remove this constructor probably
  //use the correct constructor in subclasses (->Bomb)
  Stuff() ;
  Stuff(std::string n, std::string s, std::vector<Action> &a);
} ;



class Action {
 public : 
  std::string name;
  ActionType type;
  //idem qu'au dessus
  std::vector<Stuff> parameters;
  Action (std::string n, std::string a, std::vector<Stuff> &s);
} ;

#endif
