#include <math.h>
#include "simulation.h"
#include "../generation/geography.h"
#include "../generation/tile.h"
#include "npc.h"
#include <cstdlib>
#include <iostream>
#include "position.h"

Simulation::Simulation(int MAP_SIZE,int TILE_SIZE_X,int TILE_SIZE_Y,int NB_JOUEURS,int id, Geography* map){
		this->MAP_SIZE=MAP_SIZE;
		this->TILE_SIZE_X=TILE_SIZE_X;
		this->TILE_SIZE_Y=TILE_SIZE_Y;
		this->NB_JOUEURS=NB_JOUEURS;
		this->map=map;
		this->oldMap=map;
		this->Id=id;

		int t[NB_JOUEURS];
		for(int i=0;i<NB_JOUEURS;i++){
			t[i]=0;
		}
		this->mesSous=0;
		this->sous=t;
		this->relativeTime=0;
		this->absoluteTime=0;
		this->smallTime=0;

		std::list<NPC*> NPCs;
		this->NPCs=NPCs;
}


Player* Simulation::getPlayerByID(int pid){
  Player* result = 0;
  for (std::list<Player*>::iterator it = players.begin(); it != players.end(); ++it){
    if ((*it)->getID() == pid){result = *it;};
  };
  if (result == 0) {
    std::cerr << "getPlayerByID error : Unknown playerID : " << pid << "\n" ;
    };
  return result;
}

Player* Simulation::getPlayer(){
  return this->getPlayerByID(this->Id);
};

int Simulation::isInTileX(NPC* npc){
	Position position=npc->getPosition();
	float x=position.getX();

	int i;
	i=x/TILE_SIZE_X;
	return (i);
}

int Simulation::isInTileY(NPC* npc){
	Position position=npc->getPosition();
	float y=position.getY();	
	
	int j;
	j=y/TILE_SIZE_Y;
	return (j);
}


//Simplement des casts en float de pow, sqrt et floor
float pow2(float x,float y){
	return ((float)(pow((double(x)),double(y))));
}

float sqrt2(float x){
	return ((float)(sqrt((double)x)));
}

float floor2(float x){
	return ((float)(floor((double(x)))));
}

void Simulation::ajouterNPC(int i,int j){
	Position start,target;
	int i1,i2,j1,j2;
	i1=rand()%(this->MAP_SIZE);
	i2=rand()%(this->MAP_SIZE);
	j1=rand()%(this->MAP_SIZE);
	j2=rand()%(this->MAP_SIZE);
	start=Position(i1*TILE_SIZE_X,j1*TILE_SIZE_Y);
	target=Position(i2*TILE_SIZE_X,j2*TILE_SIZE_Y);
	NPC *pnj=new NPC(20,10,10,start,target,*map,NULL);
	NPCs.push_back(pnj);
}

void Simulation::supprimerNPC(int i,int j){


}

//Crée et tue les gens dans les cases
void Simulation::peopleGeneration(){
	float chance;
	for(int i=0;i<MAP_SIZE;i++){
		for(int j=0;j<MAP_SIZE;j++){
			chance = (rand()%100);
			if(chance>(map->getTile(i,j)->getPopulationDensity()/10)){
				ajouterNPC(i,j);
			}
			if(chance<(map->getTile(i,j)->getPopulationDensity()/10)){
				supprimerNPC(i,j);
			}
		}
	}

}

//Nivelle la peur via une sorte de norme 2
void Simulation::lisserMatrice(){
	float anxiety;
	  float population;
	  *oldMap=*map;
		//interieur de la map
	  for(int i = 1; i< MAP_SIZE-2; i++){
	    for(int j = 1; i< MAP_SIZE-2; j++){
			//calcul
	      anxiety=sqrt2((1/8)*(
				2*pow2(oldMap->getAnxiety(i,j),2)+
				pow2(oldMap->getAnxiety(i-1,j),2)+
				pow2(oldMap->getAnxiety(i,j-1),2)+
				pow2(oldMap->getAnxiety(i+1,j),2)+
				pow2(oldMap->getAnxiety(i,j+1),2)+
				(1/2)*(pow2(oldMap->getAnxiety(i-1,j+1),2)+
					pow2(oldMap->getAnxiety(i+1,j+1),2)+
					pow2(oldMap->getAnxiety(i-1,j-1),2)+
					pow2(oldMap->getAnxiety(i+1,j-1),2))));
	      //set
				map->setAnxiety(i,j,anxiety);
	    }
	  }

		//bande en bas (i=0)
		for(int j=1; j< MAP_SIZE-2; j++){
			//calcul
			anxiety=sqrt2((1/6)*(
				2*pow2(oldMap->getAnxiety(0,j),2)+
				pow2(oldMap->getAnxiety(0,j-1),2)+
				pow2(oldMap->getAnxiety(1,j),2)+
				pow2(oldMap->getAnxiety(0,j+1),2)+
				(1/2)*(pow2(oldMap->getAnxiety(1,j+1),2)+
					pow2(oldMap->getAnxiety(1,j-1),2))));
			//set
			map->setAnxiety(0,j,anxiety);
	  }

		//bande à gauche (j=0)
		for(int i=1; i< MAP_SIZE-2; i++){
			//calcul
			anxiety=sqrt2((1/6)*(
				2*pow2(oldMap->getAnxiety(i,0),2)+
				pow2(oldMap->getAnxiety(i-1,0),2)+
				pow2(oldMap->getAnxiety(i+1,0),2)+
				pow2(oldMap->getAnxiety(i,0+1),2)+
				(1/2)*(pow2(oldMap->getAnxiety(i-1,0+1),2)+
					pow2(oldMap->getAnxiety(i+1,0+1),2))));
			//set
			map->setAnxiety(i,0,anxiety);
	  }

		//bande à droite (j=MAP_SIZE -1)
		for(int i=1; i< MAP_SIZE-2; i++){
			//calcul
			anxiety=sqrt2((1/6)*(
				2*pow2(oldMap->getAnxiety(i,MAP_SIZE-1),2)+
				pow2(oldMap->getAnxiety(i-1,MAP_SIZE-1),2)+
				pow2(oldMap->getAnxiety(i+1,MAP_SIZE-1),2)+
				pow2(oldMap->getAnxiety(i,MAP_SIZE-1-1),2)+
				(1/2)*(pow2(oldMap->getAnxiety(i-1,MAP_SIZE-1-1),2)+
					pow2(oldMap->getAnxiety(i+1,MAP_SIZE-1-1),2))));
			//set
			map->setAnxiety(i,MAP_SIZE-1,anxiety);
	  }

		//bande en haut (i=MAP_SIZE -1)
		for(int j=1; j< MAP_SIZE-2; j++){
			//calcul
			anxiety=sqrt2((1/6)*(
				2*pow2(oldMap->getAnxiety(MAP_SIZE-1,j),2)+
				pow2(oldMap->getAnxiety(MAP_SIZE-2,j),2)+
				pow2(oldMap->getAnxiety(MAP_SIZE-1,j-1),2)+
				pow2(oldMap->getAnxiety(MAP_SIZE-1,j+1),2)+
				(1/2)*(pow2(oldMap->getAnxiety(MAP_SIZE-2,j+1),2)+
					pow2(oldMap->getAnxiety(MAP_SIZE-2,j-1),2))));
			//set
			map->setAnxiety(MAP_SIZE-1,j,anxiety);
	  }

		//coin en haut à gauche
		anxiety=sqrt2((1/4.5)*(
			2*pow2(oldMap->getAnxiety(0,MAP_SIZE-1),2)+
			pow2(oldMap->getAnxiety(0,MAP_SIZE-2),2)+
			pow2(oldMap->getAnxiety(1,MAP_SIZE-1),2)+
			(1/2)*(pow2(oldMap->getAnxiety(1,MAP_SIZE-2),2))));
		map->setAnxiety(0,MAP_SIZE-1,anxiety);

		//coin en haut à droite
		anxiety=sqrt2((1/4.5)*(
			2*pow2(oldMap->getAnxiety(MAP_SIZE-1,MAP_SIZE-1),2)+
			pow2(oldMap->getAnxiety(MAP_SIZE-1,MAP_SIZE-2),2)+
			pow2(oldMap->getAnxiety(MAP_SIZE-2,MAP_SIZE-1),2)+
			(1/2)*(pow2(oldMap->getAnxiety(MAP_SIZE-2,MAP_SIZE-2),2))));
		map->setAnxiety(MAP_SIZE-1,MAP_SIZE-1,anxiety);

	  //coin en bas à gauche
		anxiety=sqrt2((1/4.5)*(
			2*pow2(oldMap->getAnxiety(0,0),2)+
			pow2(oldMap->getAnxiety(0,1),2)+
			pow2(oldMap->getAnxiety(1,0),2)+
			(1/2)*(pow2(oldMap->getAnxiety(1,1),2))));
		map->setAnxiety(0,0,anxiety);

		//coin en bas à droite
		anxiety=sqrt2((1/4.5)*(
			2*pow2(oldMap->getAnxiety(MAP_SIZE-1,0),2)+
			pow2(oldMap->getAnxiety(MAP_SIZE-1,1),2)+
			pow2(oldMap->getAnxiety(MAP_SIZE-2,0),2)+
			(1/2)*(pow2(oldMap->getAnxiety(MAP_SIZE-2,1),2))));
		map->setAnxiety(MAP_SIZE-1,0,anxiety);

}

void Simulation::run(sf::Time dt) {

	/*on empile les dt jusqu'à obtenir plus d'une seconde*/
	this->smallTime=smallTime+dt.asSeconds();

	/*on compte le nombre de secondes dans dt*/
	int secondes=floor2(smallTime);
	smallTime=smallTime-secondes;

	/*on n'effectue pas le lissage de la matrice plus d'une fois par seconde*/
	for(int i=1;i<secondes;i++){
		this->lisserMatrice();
	}

	/* We update the position of all the player */
	for (std::list<Player*>::iterator it = players.begin(); it != players.end(); ++it){
	  (*it)->updatePosition(dt);
	}

	/*on fait payer l'entretien des différents trucs*/
	for(int i=1;i<secondes;i++){
		for (std::list<Agent*>::iterator it = agents.begin(); it != agents.end(); ++it)
			{
				this->sous[0]=this->sous[0]-(*it)->getEntretien();
			}

		for (std::list<Camera*>::iterator it = cameras.begin(); it != cameras.end(); ++it)
			{
			this->sous[0]=this->sous[0]-(*it)->getEntretien();
			}
	}

	//Deplacement de tous les NPC.
	for (std::list<NPC *>::iterator it = NPCs.begin(); it != NPCs.end(); ++it)
	{
		int i,j;
		i=isInTileX(*it);
		j=isInTileY(*it);
		(*it)->updatePosition(dt,*map);
		int i2,j2;
		(map->getTile(i2,j2))->removeNPC(*it);
		(map->getTile(i2,j2))->addNPC(*it);
		
	}
}

int Simulation::getSous() {
	return (this->sous[0]);
}
