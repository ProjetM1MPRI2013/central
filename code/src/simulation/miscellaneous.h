/*
 * Miscellaneous.h
 *
 *  Created on: 25 nov. 2013
 *      Author: gac
 */

#ifndef MISCELLANEOUS_H_
#define MISCELLANEOUS_H_

#include "position.h"
#include <list>
class Tile;
class NPC;

class Agent {
  
 private :
  Position position;
  float entretien;//en unité/seconde
  int type;
  
 public :
  Agent(float x, float y, float entretien,int type);
  float getEntretien();
  
};

class Camera {

 private :
  Position position;
  float entretien;//en unité/seconde
  std::list<Tile*> champDeVision;

 public :
  bool isInSight(NPC& npc);
  Camera(float x, float y, float entretien, std::list<Tile*> champDeVision);
<<<<<<< HEAD
  Camera(float x, float y, float entretien);
=======

  //Quick fix, have to calculate the lineOfSight [Adrien K.]
  Camera(float x, float y, float entretien);

>>>>>>> e82cc6f248b3b6358184f735225aecf64ebda4c0
  float getEntretien();
};

#endif /* MISCELLANEOUS_H_ */
