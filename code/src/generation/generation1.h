#ifndef GENERATION1
#define GENERATION1

#include "geography.h"
#include <string>
#include <fstream>
#include "batiment.h"

class Generation1 : public Geography
{

 public:
  Generation1(std::string seed);
  std::size_t hachage(std::string seed);

 private:
  void fillBuildings(int abs0, int ord0, int abs1, int ord1, int seed, int nbLine, std::string file);
};



#endif // GENERATION1_H
