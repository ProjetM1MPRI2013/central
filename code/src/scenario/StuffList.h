/**
   @author: Remy, Adrien K.
 */


#ifndef STUFFLIST_H
#define STUFFLIST_H

#include "Stuff.h"
#include <list>


/*********************************************************
 **                    Generated code                   **
 **************/

/*********************************************************
** Weapon**
*********************************************************/
class C_Weapon: public Clickable {
public:
C_Weapon  ();
public:
virtual int getdamage () = 0;
protected:
int damage;
public:
virtual float getrange () = 0;
protected:
float range;
};

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
};

/*********************************************************
** Ammunition**
*********************************************************/
class C_Ammunition: public Clickable {
public:
C_Ammunition  (int number);
public:
int getnumber ();
public:
void setnumber (int);
protected:
int number;
};

/*********************************************************
** Bomb**
*********************************************************/
class C_Bomb: public Clickable {
public:
C_Bomb  (int power);
public:
int getpower ();
protected:
int power;
};

#endif
