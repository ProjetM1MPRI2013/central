#ifndef GENERATION1
#define GENERATION1

#include "geography.h"
#include <string>
#include <fstream>
#include "batiment.h"

class Generation1 : public Geography
{

private :
  //static const int MAP_LENGHT  = 100;
  //static const int MAP_WEIGHT = 100;
  //Tile* map[MAP_LENGHT][MAP_WEIGHT];

 public:
  Generation1(std::string seed);
  std::size_t hachage(std::string seed);
  void fillBuildings(int abs0, int ord0, int abs1, int ord1);
};



#endif // GENERATION1_H
