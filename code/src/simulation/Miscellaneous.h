/*
 * Miscellaneous.h
 *
 *  Created on: 25 nov. 2013
 *      Author: gac
 */

#ifndef MISCELLANEOUS_H_
#define MISCELLANEOUS_H_

#include "position.h"

class Agent {
	private :
Position position;
float entretien;
int type;

	public :

};

class Camera {
	private :
Position position;
float entretien;
std::list<Tile> champDeVision;
	public :
bool isInSight(NPC npc);

};



#endif /* MISCELLANEOUS_H_ */
