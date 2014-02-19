
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#include "StuffList.h"

/*********************************************************
** Stuff**
*********************************************************/
C_Stuff::C_Stuff (): Clickable () {
((Clickable*)this)->name =  "Stuff";
this->ActionTypePossible.push_back(ActionType::ToA_Drop);
};
AbstractMessage* C_Stuff::copy() {
return (AbstractMessage*) new C_Stuff(*this);
};

/*********************************************************
** Weapon**
*********************************************************/
C_Weapon::C_Weapon (): C_Stuff () {
((Clickable*)this)->name =  "Weapon";
this->ActionTypePossible.push_back(ActionType::ToA_Attack);
};

/*********************************************************
** Gun**
*********************************************************/
C_Gun::C_Gun (int ammunitionMax, float range, int damage): C_Weapon () {
((Clickable*)this)->name =  "Gun";
this->ammunitionMax = (int)ammunitionMax;
this->range = (float)range;
this->ammunitionLoaded = (int)(ammunitionMax);
this->damage = (int)damage;
this->ActionTypePossible.push_back(ActionType::ToA_Reload);
};
int C_Gun::getammunitionMax () {return this->ammunitionMax;};
float C_Gun::getrange () {return this->range;};
int C_Gun::getammunitionLoaded () {return this->ammunitionLoaded;};
void C_Gun::setammunitionLoaded ( int ammunitionLoaded ) { this->ammunitionLoaded = (int)ammunitionLoaded;};
int C_Gun::getdamage () {return this->damage;};
AbstractMessage* C_Gun::copy() {
return (AbstractMessage*) new C_Gun(*this);
};

/*********************************************************
** Mitraillette**
*********************************************************/
C_Mitraillette::C_Mitraillette (int damage): C_Gun ((int) 100, (float) 10., damage) {
((Clickable*)this)->name =  "Mitraillette";
this->ammunitionMax = (int)(100);
this->range = (float)(10.);
};
int C_Mitraillette::getammunitionMax () {return this->ammunitionMax;};
float C_Mitraillette::getrange () {return this->range;};
AbstractMessage* C_Mitraillette::copy() {
return (AbstractMessage*) new C_Mitraillette(*this);
};

/*********************************************************
** UltraM**
*********************************************************/
C_UltraM::C_UltraM (): C_Mitraillette ((int) 2000) {
((Clickable*)this)->name =  "UltraM";
this->damage = (int)(2000);
};
int C_UltraM::getdamage () {return this->damage;};
AbstractMessage* C_UltraM::copy() {
return (AbstractMessage*) new C_UltraM(*this);
};

/*********************************************************
** Knife**
*********************************************************/
C_Knife::C_Knife (): C_Weapon () {
((Clickable*)this)->name =  "Knife";
this->range = (float)(1.);
this->damage = (int)(1);
};
float C_Knife::getrange () {return this->range;};
int C_Knife::getdamage () {return this->damage;};
AbstractMessage* C_Knife::copy() {
return (AbstractMessage*) new C_Knife(*this);
};

/*********************************************************
** Ammunition**
*********************************************************/
C_Ammunition::C_Ammunition (int number): C_Stuff () {
((Clickable*)this)->name =  "Ammunition";
this->number = (int)number;
};
int C_Ammunition::getnumber () {return this->number;};
void C_Ammunition::setnumber ( int number ) { this->number = (int)number;};
AbstractMessage* C_Ammunition::copy() {
return (AbstractMessage*) new C_Ammunition(*this);
};

/*********************************************************
** Bomb**
*********************************************************/
C_Bomb::C_Bomb (int power): C_Stuff () {
((Clickable*)this)->name =  "Bomb";
this->power = (int)power;
this->ActionTypePossible.push_back(ActionType::ToA_Plant);
};
int C_Bomb::getpower () {return this->power;};
AbstractMessage* C_Bomb::copy() {
return (AbstractMessage*) new C_Bomb(*this);
};
