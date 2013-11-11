#include "Simulation.h"

void Simulation::run(sf::Time dt) {
  
  float anxiety;
  float population;

  for(int i = 1; i< MAP_SIZE-2; i++){
    for(int j = 1; i< MAP_SIZE-2; j++){
      anxiety=sqrt((1/8)*(2*pow(getAnxiety(i,j),2)+pow(getAnxiety(i-1,j),2)+pow(getAnxiety(i,j-1),2)+pow(getAnxiety(i+1,j),2)+pow(getAnxiety(i,j+1),2)+(1/2)*(pow(getAnxiety(i-1,j+1),2)+pow(getAnxiety(i+1,j+1),2)+pow(getAnxiety(i-1,j-1),2)+pow(getAnxiety(i+1,j-1),2))


      map.setAnxiety(i,j)


    }
  }
  
  
}

