
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#ifndef STUFFLIST_H
#define STUFFLIST_H
#include "Stuff.h"
#include <list>

/*********************************************************
** Stuff**
*********************************************************/
class C_Stuff: public Clickable {
 public:
C_Stuff  ();
//Serialization
protected :
virtual AbstractMessage* copy();

SIMPLE_MESSAGE(C_Stuff, Clickable);
};

/*********************************************************
** Weapon**
*********************************************************/
class C_Weapon: public C_Stuff {
 public:
C_Weapon  ();
public:
virtual int getdamage () = 0;
protected:
public:
virtual float getrange () = 0;
protected:
//Serialization
protected :

SIMPLE_MESSAGE(C_Weapon, C_Stuff);
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(C_Weapon);

/*********************************************************
** Gun**
*********************************************************/
class C_Gun: public C_Weapon {
 public:
C_Gun  (int ammunitionMax, float range, int damage);
public:
int getammunitionMax ();
protected:
int ammunitionMax; 
public:
float getrange ();
protected:
float range; 
public:
int getammunitionLoaded ();
public:
void setammunitionLoaded (int);
protected:
int ammunitionLoaded; 
public:
int getdamage ();
protected:
int damage; 
//Serialization
protected :
virtual AbstractMessage* copy();
C_Gun(){};
SIMPLE_MESSAGE(C_Gun, C_Weapon, ammunitionMax, range, ammunitionLoaded, damage);
};

/*********************************************************
** Mitraillette**
*********************************************************/
class C_Mitraillette: public C_Gun {
 public:
C_Mitraillette  (int damage);
public:
int getammunitionMax ();
protected:
int ammunitionMax; 
public:
float getrange ();
protected:
float range; 
//Serialization
protected :
virtual AbstractMessage* copy();
C_Mitraillette(){};
SIMPLE_MESSAGE(C_Mitraillette, C_Gun, ammunitionMax, range);
};

/*********************************************************
** UltraM**
*********************************************************/
class C_UltraM: public C_Mitraillette {
 public:
C_UltraM  ();
public:
int getdamage ();
protected:
int damage; 
//Serialization
protected :
virtual AbstractMessage* copy();

SIMPLE_MESSAGE(C_UltraM, C_Mitraillette, damage);
};

/*********************************************************
** Knife**
*********************************************************/
class C_Knife: public C_Weapon {
 public:
C_Knife  ();
public:
float getrange ();
protected:
float range; 
public:
int getdamage ();
protected:
int damage; 
//Serialization
protected :
virtual AbstractMessage* copy();

SIMPLE_MESSAGE(C_Knife, C_Weapon, range, damage);
};

/*********************************************************
** Ammunition**
*********************************************************/
class C_Ammunition: public C_Stuff {
 public:
C_Ammunition  (int number);
public:
int getnumber ();
public:
void setnumber (int);
protected:
int number; 
//Serialization
protected :
virtual AbstractMessage* copy();
C_Ammunition(){};
SIMPLE_MESSAGE(C_Ammunition, C_Stuff, number);
};

/*********************************************************
** Bomb**
*********************************************************/
class C_Bomb: public C_Stuff {
 public:
C_Bomb  (int power);
public:
int getpower ();
protected:
int power; 
//Serialization
protected :
virtual AbstractMessage* copy();
C_Bomb(){};
SIMPLE_MESSAGE(C_Bomb, C_Stuff, power);
};

#endif