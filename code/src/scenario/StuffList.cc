#include "StuffList.h"


/*********************************************************
 **                    Generated code                   **
 *********************************************************/


/*********************************************************
** Weapon**
*********************************************************/
C_Weapon::C_Weapon (): Clickable () {
((Clickable*)this)->name =  "N_Weapon";
this->ActionTypePossible.push_back(ActionType::ToA_Attack);
};

/*********************************************************
** Gun**
*********************************************************/
C_Gun::C_Gun (int ammunitionMax, float range, int damage) : C_Weapon () {
((Clickable*)this)->name =  "N_Gun";
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

/*********************************************************
** Mitraillette**
*********************************************************/
C_Mitraillette::C_Mitraillette (int damage): C_Gun ((int) 100, (float) 10., damage) {
((Clickable*)this)->name =  "N_Mitraillette";
this->ammunitionMax = (int)(100);
this->range = (float)(10.);
};
int C_Mitraillette::getammunitionMax () {return this->ammunitionMax;};
float C_Mitraillette::getrange () {return this->range;};

/*********************************************************
** UltraM**
*********************************************************/
C_UltraM::C_UltraM (): C_Mitraillette ((int) 2000) {
((Clickable*)this)->name =  "N_UltraM";
this->damage = (int)(2000);
};
int C_UltraM::getdamage () {return this->damage;};

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

/*********************************************************
** Ammunition**
*********************************************************/
C_Ammunition::C_Ammunition (int number): Clickable () {
((Clickable*)this)->name =  "N_Ammunition";
this->number = (int)number;
};
int C_Ammunition::getnumber () {return this->number;};
void C_Ammunition::setnumber ( int number ) { this->number = (int)number;};

/*********************************************************
** Bomb**
*********************************************************/
C_Bomb::C_Bomb (int power): Clickable () {
((Clickable*)this)->name =  "N_Bomb";
this->power = (int)power;
this->ActionTypePossible.push_back(ActionType::ToA_Plant);
};
int C_Bomb::getpower () {return this->power;};
