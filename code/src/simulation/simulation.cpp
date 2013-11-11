#include "Simulation.h"


Tile& Simulation::isInTile(NPC npc){
	Position position=npc.getPosition();
	float x=position.getX();
	float y=position.getY();	
	
	int i,j;
	i=x/TILE_SIZE_X;
	j=y/TILE_SIZE_Y;
	return (map.getTile(i,j));
}


void Simulation::run(sf::Time dt) {
  
  float anxiety;
  float population;

	//interieur de la map
  for(int i = 1; i< MAP_SIZE-2; i++){
    for(int j = 1; i< MAP_SIZE-2; j++){
			//calcul
      anxiety=sqrt((1/8)*(
				2*pow(oldMap.getAnxiety(i,j),2)+
				pow(oldMap.getAnxiety(i-1,j),2)+
				pow(oldMap.getAnxiety(i,j-1),2)+
				pow(oldMap.getAnxiety(i+1,j),2)+
				pow(oldMap.getAnxiety(i,j+1),2)+
				(1/2)*(pow(oldMap.getAnxiety(i-1,j+1),2)+
					pow(oldMap.getAnxiety(i+1,j+1),2)+
					pow(oldMap.getAnxiety(i-1,j-1),2)+
					pow(oldMap.getAnxiety(i+1,j-1),2))));
      //set
			map.setAnxiety(i,j,anxiety);
    }
  }
  
	//bande en bas (i=0)
	for(int j=1; j< MAP_SIZE-2; j++){
		//calcul
		anxiety=sqrt((1/6)*(
			2*pow(oldMap.getAnxiety(0,j),2)+
			pow(oldMap.getAnxiety(0,j-1),2)+
			pow(oldMap.getAnxiety(1,j),2)+
			pow(oldMap.getAnxiety(0,j+1),2)+
			(1/2)*(pow(oldMap.getAnxiety(1,j+1),2)+
				pow(oldMap.getAnxiety(1,j-1),2))));
		//set
		map.setAnxiety(0,j,anxiety);
  }

	//bande à gauche (j=0)
	for(int i=1; i< MAP_SIZE-2; i++){
		//calcul
		anxiety=sqrt((1/6)*(
			2*pow(oldMap.getAnxiety(i,0),2)+
			pow(oldMap.getAnxiety(i-1,0),2)+
			pow(oldMap.getAnxiety(i+1,0),2)+
			pow(oldMap.getAnxiety(i,0+1),2)+
			(1/2)*(pow(oldMap.getAnxiety(i-1,0+1),2)+
				pow(oldMap.getAnxiety(i+1,0+1),2))));
		//set
		map.setAnxiety(i,0,anxiety);
  }
		
	//bande à droite (j=MAP_SIZE -1)
	for(int i=1; i< MAP_SIZE-2; i++){
		//calcul
		anxiety=sqrt((1/6)*(
			2*pow(oldMap.getAnxiety(i,MAP_SIZE-1),2)+
			pow(oldMap.getAnxiety(i-1,MAP_SIZE-1),2)+
			pow(oldMap.getAnxiety(i+1,MAP_SIZE-1),2)+
			pow(oldMap.getAnxiety(i,MAP_SIZE-1-1),2)+
			(1/2)*(pow(oldMap.getAnxiety(i-1,MAP_SIZE-1-1),2)+
				pow(oldMap.getAnxiety(i+1,MAP_SIZE-1-1),2))));
		//set
		map.setAnxiety(i,MAP_SIZE-1,anxiety);
  }

	//bande en haut (i=MAP_SIZE -1)
	for(int j=1; j< MAP_SIZE-2; j++){
		//calcul
		anxiety=sqrt((1/6)*(
				2*pow(oldMap.getAnxiety(MAP_SIZE-1,j),2)+
				pow(oldMap.getAnxiety(MAP_SIZE-2,j),2)+
				pow(oldMap.getAnxiety(MAP_SIZE-1,j-1),2)+
				pow(oldMap.getAnxiety(MAP_SIZE-1,j+1),2)+
				(1/2)*(pow(oldMap.getAnxiety(MAP_SIZE-2,j+1),2)+
					pow(oldMap.getAnxiety(MAP_SIZE-2,j-1),2))));
		//set
		map.setAnxiety(MAP_SIZE-1,j,anxiety);
  }

	//coin en haut à gauche
	anxiety=sqrt((1/4.5)*(
		2*pow(oldMap.getAnxiety(0,MAP_SIZE-1),2)+
		pow(oldMap.getAnxiety(0,MAP_SIZE-2),2)+
		pow(oldMap.getAnxiety(1,MAP_SIZE-1),2)+
		(1/2)*(pow(oldMap.getAnxiety(1,MAP_SIZE-2),2))));
	map.setAnxiety(0,MAP_SIZE-1,anxiety);

	//coin en haut à droite
	anxiety=sqrt((1/4.5)*(
		2*pow(oldMap.getAnxiety(MAP_SIZE-1,MAP_SIZE-1),2)+
		pow(oldMap.getAnxiety(MAP_SIZE-1,MAP_SIZE-2),2)+
		pow(oldMap.getAnxiety(MAP_SIZE-2,MAP_SIZE-1),2)+
		(1/2)*(pow(oldMap.getAnxiety(MAP_SIZE-2,MAP_SIZE-2),2))));
	map.setAnxiety(MAP_SIZE-1,MAP_SIZE-1,anxiety);

  //coin en bas à gauche
	anxiety=sqrt((1/4.5)*(
		2*pow(oldMap.getAnxiety(0,0),2)+
		pow(oldMap.getAnxiety(0,1),2)+
		pow(oldMap.getAnxiety(1,0),2)+
		(1/2)*(pow(oldMap.getAnxiety(1,1),2))));
	map.setAnxiety(0,0,anxiety);

	//coin en bas à droite
	anxiety=sqrt((1/4.5)*(
		2*pow(oldMap.getAnxiety(MAP_SIZE-1,0),2)+
		pow(oldMap.getAnxiety(MAP_SIZE-1,1,2)+
		pow(oldMap.getAnxiety(MAP_SIZE-2,0),2)+
		(1/2)*(pow(oldMap.getAnxiety(MAP_SIZE-2,1),2))));
	map.setAnxiety(MAP_SIZE-1,0,anxiety);

	//Deplacement de tous les NPC.
	for (List<NPC>::iterator it = NPCs.begin(); it != L.end(); ++it)
	{
		(*it).updateTrajectory(dt);
		map.addNPC(i,j,NPC);
		
	}

	
	
}

