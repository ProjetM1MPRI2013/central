/*
 * Miscellaneous.h
 *
 *  Created on: 25 nov. 2013
 *      Author: gac
 */

#ifndef MISCELLANEOUS_H_
#define MISCELLANEOUS_H_

#include "position.h"
#include "positionable.h"
#include <list>
class Tile;
class NPC;

class Agent : public Positionable {
  
 private :
  float entretien;//en unité/seconde
  int type;
  
 public :
  Agent(float x, float y, float entretien,int type);
  float getEntretien();
  
};

class Camera : public Positionable {

 private :
  float entretien;//en unité/seconde
  int type;

 public :
  bool isInSight(NPC& npc);
  Camera(float x, float y, float entretien, int type);

  //Quick fix, have to calculate the lineOfSight [Adrien K.]


  float getEntretien();
};

#endif /* MISCELLANEOUS_H_ */
