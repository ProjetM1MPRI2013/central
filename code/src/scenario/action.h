#ifndef ACTION_H
#define ACTION_H


/**
 * @brief StuffType.
 * there is 3 type of Stuff : object, character and internet.
 * an exemple of subtype is explosive.
 */

class Stuff {
 public :
  string name;
  string type;
/**
 * @brief actionPossible.
 * A vector of type of action possible with this stuff.
 */
  Action[] actionPossible;
  Stuff (string n, string s, Action[] a)
}



class Action {
 public : 
  string name;
  ActionType type;
  Stuff[] parameters;
  Action (string n, string a, Stuff[] s)
}

#endif
