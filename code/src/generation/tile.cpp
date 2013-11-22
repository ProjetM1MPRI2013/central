#include "tile.h"


enum TileType {roadH, roadV, intersection, banque, immeuble}; // énumération des types de batiments

Tile::Tile(int abs, int ord, TileType typeO, bool destructibleO, float anxietyO, float populationDensityO, bool gohO, bool gouO, bool gorO, bool golO, float speedO, Coordinates batOriginO, Coordinates boroughOrigin) {
  coord = new Coordinates(abs, ord);
  type = typeO;
  destructible = destructibleO;
  anxiety = anxietyO;
  populationDensity = populationDensityO;
  goh = gohO;
  gou = gouO;
  gol = golO;
  gor = gorO;
  speed = speedO;
  batOrigin = batOriginO;
  lenghtBat = getTLenght(typeO);
  weightBat = getTWeight(typeO);
  sprite = getTSprite(typeO); //à modifier, car cela dépend si origine ou pas 
  destructionLevel = 0.;
  coordBorough = boroughOrigin;
}



Tile::getTLenght(TileType type) {
  switch (type) {
  case roadH: break;
  case roadV: break;
  case intersection: break;
  case banque: break;
  case immeuble: break;
  }
}

Tile::getTWeight(TileType type) {
  switch (type) {
  case roadH: break;
  case roadV: break;
  case intersection: break;
  case banque: break;
  case immeuble: break;
  }
}

Tile::getTSprite(TileType type) {
  switch (type) {
  case roadH: break;
  case roadV: break;
  case intersection: break;
  case banque: break;
  case immeuble: break;
  }
}
