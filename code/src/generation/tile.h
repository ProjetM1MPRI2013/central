#ifndef TILE
#define TILE

#include <list>
#include <iostream>
#include <cerrno>
#include <SFML/Graphics.hpp>

enum TileType {ROADH, ROADV, INTER, BANK, HOUSE, BLANK}; // énumération des types de batiments


class NPC;
class TileWrapper;


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
  /**
   * abscissa 
   */ 
  int abs;
  /**
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

  /**
   * @brief equals
   * returns true iff the abs and ord of the Coordinates are equal to those of the other Coordinates
   * @param c: the Coordinates to compare
   */
  bool equals(Coordinates& c);
};
opulationDensity, bool goh, bool gou, bool gor, bool gol, float speed, Coordinates& batOrigin, Coordinates& boroughOrigin, SpriteTilePack* stp);
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
     * @brief equals
     * returns true iff the Tile is has the same coordinatees as the other tile
     * @param t: the Tile to compare
     */
    bool equals(Tile& t);

    TileWrapper* getWrapper();
    void setWrapper(TileWrapper*);
    void resetWrapper();
    
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
