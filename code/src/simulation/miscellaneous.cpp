/*
 * Mischellaneous.cpp
 *
 *  Created on: 25 nov. 2013
 *      Author: gac
 */

#include "miscellaneous.h";

bool isInList(NPC& a,std::list<NPC&> b){
	NPC& currentNPC;
	bool boolean(false);
	for (std::list<NPC&>::iterator it = b.begin(); it != b.end(); ++it)
			{
				currentNPC=(*it);
				boolean=boolean||(currentNPC==a);
			}
	return boolean;
}


Agent::Agent(float x, float y, float entretien, int type){
	this->entretien=entretien;
	this->type=type;
	this->position=Position(x,y);
	this->type=type;
}

float Agent::getEntretien(){
	return (this->entretien);
}

Camera::Camera(float x,float y,float entretien, std::list<Tile&> lineOfSight) {
	this->entretien=entretien;
	this->position=Position(x,y);
	this->champDeVision=lineOfSight;
}

bool Camera::isInSight(NPC& npc){
	bool boolean=false;
	std::list<NPC&>NPCinTile;
	for (std::list<Tile&>::iterator it = this->champDeVision.begin(); it != this->champDeVision.end(); ++it)
		{
			NPCinTile=(*it).getNPCs();
			boolean=boolean||(isInList(npc,NPCinTile));
		}
	return boolean;
}

float Camera::getEntretien(){
	return (this->entretien);
}

