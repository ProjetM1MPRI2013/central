#ifndef TILE
#define TILE

#include <list>
#include <iostream>
#include <cerrno>
#include <SFML/Graphics.hpp>

enum TileType {ROADH, ROADV, INTER, BANK, HOUSE, BLANK}; // énumération des types de batiments


class NPC;

struct SpriteTilePack
{
  sf::Texture texture;
  // Ces coordonnées correspondent au point d'origine de l'image dans la boite de la texture
  int originX;
  int originY;
  // Ces variables correspondent à la boite qui encadre l'image dans la texture
  int X1;
  int Y1;
  int X2;
  int Y2;
};

/**
 * @brief Coordinates
 * Useful to caracterize a tile in the map
 */
class Coordinates {
 private:
  /*
   * abscissa 
   */ 
  int abs;
  /*
   * ordinate 
   */
  int ord;
 public:
  /**
   * @brief create a point, with an abscissa and an ordinate
   * @param abs : the abscissa
   * @param ord : the ordinate
   */
  Coordinates(int abs, int ord);

  /**
   * @brief get the abscissa
   */ 
  int getAbs();
  /**
   * @brief set the abscissa
   * @param abs : the new abscissa
   */
  void setAbs(int abs);
  /**
   * @brief get the abscissa ordinate
   */ 
  int getOrd();
  /**
   * @brief set the ordinate
   * @param abs : the new ordinate
   */
  void setOrd(int ord);
};


/**
 * @brief A tile of the map
 */
class Tile {

 private:
  /*
   * type of the batiment of the case
   */
  TileType type;
  sf::Sprite sprite;
  SpriteTilePack* stp;
  bool destructible;
  float anxiety;
  float populationDensity;
  float destructionLevel;
  /*
   * possibility to go straight
   */
  bool goh;
  /*
   * possibility to go above, between 0 and 1
   */
  bool gou;
  /*
   * possibility to go to the right, between 0 and 1
   */
  bool gor;
  /*
   * possibility to go to the left, between 0 and 1
   */
  bool gol;
  /*
   * caracterisation of the speed into the tile, between 0 and 1
   */
  float speed;
  /*
   * the origin of the batiment, which is rectangular (we can decompose a batiment)
   */
  Coordinates& batOrigin;
  /*
   * total lenght of the bat
   */
  int lenghtBat;
  /*
   * total weight of the bat
   */
  int weightBat;
  /*
   * coordinates of the tile
   */
  Coordinates coord;
  /*
   * coordinates of the caracteristic tile of the borough of our tile
   */
  Coordinates& coordBorough;

  /**
   * @brief List of the NPC currently in the tile
   */
  std::list<NPC*> listNPC;

  /**
   * @brief lenght of a bat thanks to its type
   * @param type : type of the batiment
   * @return the lenght of the bat
   */
  float getTLenght(TileType type);
  /**
   * @brief weight of a bat thanks to its type
   * @param type : type of the batiment
   * @return the weight of the bat
   */
  float getTWeight(TileType type);
  /**
   * @brief sprite of the bat thanks to its type
   * @param type : type of the batiment
   * @return the sprite of the bat
   */
  // sf::Sprite& getTSprite(TileType type);
  
  public:
  /**
   * @brief create a tile
   * @param abs : the abscissa of the coordinates of the tile in the map
   * @param ord : the ordinate of the coordinates of the tile in the map
   * @param type : type of the bat
   * @param destructible : is this bat destructible
   * @param anxiety : initial anxiety into the tile
   * @param populationDensity : initial population density into the tile
   * @param goh : initial possibility to go straight
   * @param gou : initial possibility to go above
   * @param gor : initial possibility to go to the right
   * @param gol : initial possibility to go to the left
   * @param speed : initial speed into the tile
   * @param batOrigin : caracteristic point of the bat
   * @param boroughOrigin : initial borough of the tile
   * @param stp : the informations about the texture of the tile
   */
  Tile(int abs, int ord, TileType type, bool destructible, float anxiety, float populationDensity, bool goh, bool gou, bool gor, bool gol, float speed, Coordinates& batOrigin, Coordinates& boroughOrigin, SpriteTilePack* stp);
    TileType getType();
    void setType(TileType t);
    bool isDestructible();
    float getAnxiety();
    void setAnxiety(float a);
    float getPopulationDensity();
    void setPopulationDensity(float d);
    float getDestructionLevel();
    void setDestructionLevel(float dl);
    bool getGoh();
    void setGoh(bool goh);
    bool getGou();
    void setGou(bool gou);
    bool getGor();
    void setGor(bool gor);
    bool getGol();
    void setGol(bool gol);
    float getSpeed();
    void setSpeed(float speed);
    Coordinates& getBatOrigin();
    void setBatOrigin(Coordinates& p);
    int getLenghtBat();
    void setLenghtBat(int l);
    int getWeightBat();
    void setWeightBat(int w);
    sf::Sprite getSprite();
    Coordinates& getCoord();
    void setCoord(Coordinates& coord);

    /**
     * @brief Return the list of the NPC in the tile, sorted by x-y
     */
    std::list<NPC*> getNPCs();

    void addNPC (NPC* a);
    void removeNPC (NPC* a);
    
    /**
     *@brief The tile belongs to a borough caracterized by a tile, given by this function
     *@return the caracteristic tile of the borough
     */
    Coordinates& getCoordBorough();
    /**
     *@brief Change the borough of the tile
     */
    void setCoordBorough(Coordinates& CBorough);
    
    /**
     *@brief Sets the texture of the tile
     */
    void setTexture(SpriteTilePack* stp);
    
    /**
     *@brief Get the origin X of the building in the texture
     */
    int getOriginSpriteX();
    
    /**
     *@brief Get the origin Y of the building in the texture
     */
    int getOriginSpriteY();
    
};





#endif // TILE_H
