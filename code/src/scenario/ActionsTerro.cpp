#include "ActionsTerro.h"

Drop :: Drop (Stuff* s) : Action ("Drop") {
  stu = s;
};

Attack :: Attack (Weapon* weapon,NPC* victim)  : Action ("Attack") {
  vict = victim;
  weap = weapon;
  int damage () = 3 ;/*todo*/
    };


Plant :: Plant (Bomb* bomb,Clicable zone )  : Action ("Plant") {
  bo = bomb;
  z = zone;
};

Reload (Gun gun,Ammunition ammunition) : Action ("Reload") {
  g = gun;
  ammu = ammunition;
    };

 

 

