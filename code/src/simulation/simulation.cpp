#include "simulation.h"
#include <math.h>

Tile& Simulation::isInTile(NPC npc){
	Position position=npc.getPosition();
	float x=position.getX();
	float y=position.getY();	
	
	int i,j;
	i=x/TILE_SIZE_X;
	j=y/TILE_SIZE_Y;
	return (map.getTile(i,j));
}

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

float pow2(float x,float y){
	return ((float)(pow((double(x)),double(y))));
}

float sqrt2(float x){
	return ((float)(sqrt((double)x)));
}

float floor2(float x){
	return ((float)(floor((double(x)))));
}

/*float pow2(int i,int j){
	return ((float)(pow((int)i,(int)j)));
}*/
void Simulation::lisserMatrice(){
	float anxiety;
	  float population;

		//interieur de la map
	  for(int i = 1; i< MAP_SIZE-2; i++){
	    for(int j = 1; i< MAP_SIZE-2; j++){
			//calcul
	      anxiety=sqrt2((1/8)*(
				2*pow2(oldMap.getAnxiety(i,j),2)+
				pow2(oldMap.getAnxiety(i-1,j),2)+
				pow2(oldMap.getAnxiety(i,j-1),2)+
				pow2(oldMap.getAnxiety(i+1,j),2)+
				pow2(oldMap.getAnxiety(i,j+1),2)+
				(1/2)*(pow2(oldMap.getAnxiety(i-1,j+1),2)+
					pow2(oldMap.getAnxiety(i+1,j+1),2)+
					pow2(oldMap.getAnxiety(i-1,j-1),2)+
					pow2(oldMap.getAnxiety(i+1,j-1),2))));
	      //set
				map.setAnxiety(i,j,anxiety);
	    }
	  }

		//bande en bas (i=0)
		for(int j=1; j< MAP_SIZE-2; j++){
			//calcul
			anxiety=sqrt2((1/6)*(
				2*pow2(oldMap.getAnxiety(0,j),2)+
				pow2(oldMap.getAnxiety(0,j-1),2)+
				pow2(oldMap.getAnxiety(1,j),2)+
				pow2(oldMap.getAnxiety(0,j+1),2)+
				(1/2)*(pow2(oldMap.getAnxiety(1,j+1),2)+
					pow2(oldMap.getAnxiety(1,j-1),2))));
			//set
			map.setAnxiety(0,j,anxiety);
	  }

		//bande à gauche (j=0)
		for(int i=1; i< MAP_SIZE-2; i++){
			//calcul
			anxiety=sqrt2((1/6)*(
				2*pow2(oldMap.getAnxiety(i,0),2)+
				pow2(oldMap.getAnxiety(i-1,0),2)+
				pow2(oldMap.getAnxiety(i+1,0),2)+
				pow2(oldMap.getAnxiety(i,0+1),2)+
				(1/2)*(pow2(oldMap.getAnxiety(i-1,0+1),2)+
					pow2(oldMap.getAnxiety(i+1,0+1),2))));
			//set
			map.setAnxiety(i,0,anxiety);
	  }

		//bande à droite (j=MAP_SIZE -1)
		for(int i=1; i< MAP_SIZE-2; i++){
			//calcul
			anxiety=sqrt2((1/6)*(
				2*pow2(oldMap.getAnxiety(i,MAP_SIZE-1),2)+
				pow2(oldMap.getAnxiety(i-1,MAP_SIZE-1),2)+
				pow2(oldMap.getAnxiety(i+1,MAP_SIZE-1),2)+
				pow2(oldMap.getAnxiety(i,MAP_SIZE-1-1),2)+
				(1/2)*(pow2(oldMap.getAnxiety(i-1,MAP_SIZE-1-1),2)+
					pow2(oldMap.getAnxiety(i+1,MAP_SIZE-1-1),2))));
			//set
			map.setAnxiety(i,MAP_SIZE-1,anxiety);
	  }

		//bande en haut (i=MAP_SIZE -1)
		for(int j=1; j< MAP_SIZE-2; j++){
			//calcul
			anxiety=sqrt2((1/6)*(
				2*pow2(oldMap.getAnxiety(MAP_SIZE-1,j),2)+
				pow2(oldMap.getAnxiety(MAP_SIZE-2,j),2)+
				pow2(oldMap.getAnxiety(MAP_SIZE-1,j-1),2)+
				pow2(oldMap.getAnxiety(MAP_SIZE-1,j+1),2)+
				(1/2)*(pow2(oldMap.getAnxiety(MAP_SIZE-2,j+1),2)+
					pow2(oldMap.getAnxiety(MAP_SIZE-2,j-1),2))));
			//set
			map.setAnxiety(MAP_SIZE-1,j,anxiety);
	  }

		//coin en haut à gauche
		anxiety=sqrt2((1/4.5)*(
			2*pow2(oldMap.getAnxiety(0,MAP_SIZE-1),2)+
			pow2(oldMap.getAnxiety(0,MAP_SIZE-2),2)+
			pow2(oldMap.getAnxiety(1,MAP_SIZE-1),2)+
			(1/2)*(pow2(oldMap.getAnxiety(1,MAP_SIZE-2),2))));
		map.setAnxiety(0,MAP_SIZE-1,anxiety);

		//coin en haut à droite
		anxiety=sqrt2((1/4.5)*(
			2*pow2(oldMap.getAnxiety(MAP_SIZE-1,MAP_SIZE-1),2)+
			pow2(oldMap.getAnxiety(MAP_SIZE-1,MAP_SIZE-2),2)+
			pow2(oldMap.getAnxiety(MAP_SIZE-2,MAP_SIZE-1),2)+
			(1/2)*(pow2(oldMap.getAnxiety(MAP_SIZE-2,MAP_SIZE-2),2))));
		map.setAnxiety(MAP_SIZE-1,MAP_SIZE-1,anxiety);

	  //coin en bas à gauche
		anxiety=sqrt2((1/4.5)*(
			2*pow2(oldMap.getAnxiety(0,0),2)+
			pow2(oldMap.getAnxiety(0,1),2)+
			pow2(oldMap.getAnxiety(1,0),2)+
			(1/2)*(pow2(oldMap.getAnxiety(1,1),2))));
		map.setAnxiety(0,0,anxiety);

		//coin en bas à droite
		anxiety=sqrt2((1/4.5)*(
			2*pow2(oldMap.getAnxiety(MAP_SIZE-1,0),2)+
			pow2(oldMap.getAnxiety(MAP_SIZE-1,1),2)+
			pow2(oldMap.getAnxiety(MAP_SIZE-2,0),2)+
			(1/2)*(pow2(oldMap.getAnxiety(MAP_SIZE-2,1),2))));
		map.setAnxiety(MAP_SIZE-1,0,anxiety);

}

void Simulation::run(sf::Time dt) {
  
	/*on empile les dt jusqu'à obtenir plus d'une seconde*/
	this->smallTime=smallTime+dt;

	/*on compte le nombre de secondes dans dt*/
	int secondes=floor2(smallTime);
	smallTime=smallTime-secondes;

	/*on n'effectue pas le lissage de la matrice plus d'une fois par seconde*/
	for(int i=1;i<secondes;i++){
		this->lisserMatrice();
	}

	/*on fait payer l'entretien des différents trucs*/
	for(int i=1;i<secondes;i++){
		for (std::list<Agent>::iterator it = agents.begin(); it != agents.end(); ++it)
			{
				this->sous=this->sous-(*it).getEntretien();
			}

		for (std::list<Camera>::iterator it = cameras.begin(); it != cameras.end(); ++it)
			{
			this->sous=this->sous-(*it).getEntretien();
			}
	}

	//Deplacement de tous les NPC.
	/*for (std::list<NPC>::iterator it = NPCs.begin(); it != NPCs.end(); ++it)
	{
		(*it).updateTrajectory(dt);
		map.addNPC(i,j,NPC);
		
	}
	*/
	
	
}

