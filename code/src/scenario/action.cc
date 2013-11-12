#include "cscenarioi.h"
#include "action.h"

using namespace std ;

//already declared in .h
//class Stuff {
// public :
//  string name;
//  string type;
//  ActionType[] actionPossible;
//  Stuff (string n, string  s, Action[] a)=
//  {name = n; type = s;actionPossible = a }
//};

Stuff::Stuff(string n, string s, std::vector<Action> &a) :
    name(n), type(s), actionPossible(a) {}


//Already declared in .h
//class Action {
// public :
//  string name;
//  string type;
//  Stuff[] parameters;
//  Action (string n, string  a, Stuff[] s) = {name = n; type = a ; parameters = s }
//};

Action::Action(string n, string a, std::vector<Stuff> &s) :
    name(n), type(a), parameters(s) {}



class Bomb: public Stuff {
   string trigger;
   int power;
   string type;
   Bomb (string t, int p, string s){
       trigger = t;
       power = p ;
       type = s ;
   }
};

class Knife: public Stuff {
  int material; /* 0 metal, 1 plastic */
  Knife (int m) {material = m ;}
};

class Ammunition : public Stuff {
  int number;
  string type; /* "handgun", "rifle", "automatic rifle" */
  Ammunition (int n, string f, int s ){
      //not sure of that...
      number = n ;
      //not declared
      //firearm = f;
      //silent = s ;
  }
};

class FireArme : public Stuff {
  string type; /* "handgun", "rifle", "automatic rifle" */
  int silencer; /* 0 no, 1 yes */
} ;





