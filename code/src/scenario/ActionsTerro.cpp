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

Reload (Gun gun) : Action ("Reload") {
  g = gun;
    };

void Reload::doAction(){
  date = time(0); //TODO: change this to the boost way to calculate with milliseconds
  //send to the server the request to save this action (add to the waiting list)
}
