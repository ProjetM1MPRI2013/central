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

  //Quick fix, have to calculate the lineOfSight [Adrien K.]
  Camera(float x, float y, float entretien);

  float getEntretien();
};

#endif /* MISCELLANEOUS_H_ */
