/**
 * @author: MrKulu
 */

#include "fogDisabler.h"


FogDisabler::FogDisabler() {
  radius = 0;
  active = false;
}

FogDisabler::FogDisabler(int rad, bool active_init) {
  radius = rad;
  active = active_init;
}

void FogDisabler::setActive(bool act) {
  active = act;
  return;
}

void FogDisabler::setRadius(int rad) {
  radius = rad;
  return;
}

bool FogDisabler::getActive() {
  return active;
}

int FogDisabler::getRadius() {
  return radius;
}

