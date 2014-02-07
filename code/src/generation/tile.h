/**
 * @author: Maxime, Joseph
 */
#ifndef TILE
#define TILE

#include <list>
#include <iostream>
#include <cerrno>
#include <SFML/Graphics.hpp>
#include <string>

enum TileType {ROADH, ROADV, INTER, BANK, HOUSE, BLANK}; // énumération des types de batiments


class NPC;
class TileWrapper;
class Geography;

class SpriteTilePack
{
 public:
  sf::Texture texture;
  // Ces coordonnées correspondent au point d'origine de l'image dans la boite de la texture
  int originX;
  int originY;
};




/**
 * @brief Coordinates
 * Useful to caracterize a tile in the map
 */
class Coordinates {
 public:
  /**
   * abscissa 
   */ 
  int abs;
  /**
   * ordinate 
   */
  int ord;

  /**
   * @brief create a point, with an abscissa and an ordinate
   * @param abs : the abscissa
   * @param ord : the ordinate
   */

  Coordinates();
  Coordinates(int abs, int ord);
  Coordinates(const Coordinates& a);

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

/**
 * @brief A tile of the map
 */
class Tile {

 private:
  /**
   * type of the batiment of the case
   */
  TileType type;
  sf::Sprite sprite;
  SpriteTilePack* stp;
  bool destructible;
  float anxiety;
  float populationDensity;
  float destructionLevel;
  /**
   * possibility to go up, ie to go the Tile (i,j+1)
   */
  bool gou;
  /**
   * possibility to go down, ie to go the Tile (i,j-1)
   */
  bool god;
  /**
   * possibility to go to the right, ie to go to the Tile (i+1,j)
   */
  bool gor;
  /**
   * possibility to go to the left, ie to go to the Tile (i-1,j)
   */
  bool gol;
  /**
   * caracterisation of the speed into the tile, between 0 and 1
   */
  float speed;
  /**
   * the origin of the batiment, which is rectangular (we can decompose a batiment)
   */
  Coordinates batOrigin;
  /**
   * total width of the bat
   */
  int widthBat;
  /**
   * total height of the bat
   */
  int heightBat;
  /**
   * coordinates of the tile
   */
  Coordinates coord;
  /**
   * coordinates of the caracteristic tile of the borough of our tile
   */
  Coordinates coordBorough;

  /**
   * the name of the file where the sprite of the building of the tile is
   */
  std::string filePictures;
  
  /**
   * the position of the sprite of the building of the tile in the file
   */
  Coordinates picture;

  /**
   * @brief List of the NPC currently in the tile
   */
  std::list<NPC*> listNPC;


  /**
   * @brief sprite of the bat thanks to its type
   * @param type : type of the batiment
   * @return the sprite of the bat
   */
  // sf::Sprite& getTSprite(TileType type);

  TileWrapper* wrapper;
  bool alpha;
  bool fog;
  bool buildfog;

  public:
  /**
   * @brief create a tile
   * @param abs : the abscissa of the coordinates of the tile in the map
   * @param ord : the ordinate of the coordinates of the tile in the map
   * @param type : type of the bat
   * @param destructible : is this bat destructible
   * @param anxiety : initial anxiety into the tile
   * @param populationDensity : initial population density into the tile
   * @param gou : initial possibility to go up, ie to go the Tile (i,j+1)
   * @param god : initial possibility to go down, ie to go the Tile (i,j-1)
   * @param gor : initial possibility to go to the right, ie to go to the Tile (i+1,j)
   * @param gol : initial possibility to go to the left, ie to go to the Tile (i-1,j)
   * @param speed : initial speed into the tile
   * @param batOrigin : caracteristic point of the bat
   * @param boroughOrigin : initial borough of the tile
   * @param stp : the informations about the texture of the tile
   * @param filePicturesO : the name of the file where the sprite of the building of the tile is
   * @param pictureO : he position of the sprite of the building of the tile in the file
   * @param widthO : the width of the building of the tile
   * @param height0 : the height of the building of the tile
   * The batOrigin and the boroughOrigin argument are copied during the construction, they can be deleted after the call to the constructo
   */
  Tile(int abs, int ord, TileType type, bool destructible, float anxiety, float populationDensity, bool gou, bool god, bool gor, bool gol, float speed, Coordinates batOrigin, Coordinates boroughOrigin, SpriteTilePack* stp, std::string filePicturesO, Coordinates pictureO, int widthO, int heightO);

  Tile();

  Tile(const Tile&);
  Tile& operator=(const Tile&);


    /**
     * @brief gives the type of the tile, it's a generalist type
     * @return the type of the tile, which is in a enum
     */
    TileType getType();
    /**
     * 
     */
    void setType(TileType t);
    bool isDestructible();
    void nobodyTile ();
    float getAnxiety();
    void setAnxiety(float a);
    float getPopulationDensity();
    void setPopulationDensity(float d);
    float getDestructionLevel();
    void setDestructionLevel(float dl);
    bool getGou();
    void setGou(bool gou);
    bool getGod();
    void setGod(bool god);
    bool getGor();
    void setGor(bool gor);
    bool getGol();
    void setGol(bool gol);
    float getSpeed();
    void setSpeed(float speed);
    Coordinates& getBatOrigin();
    void setBatOrigin(Coordinates& p);
    int getWidthBat();
    void setWidthBat(int w);
    int getHeightBat();
    void setHeightBat(int h);
    sf::Sprite& getSprite();
    Coordinates& getCoord();
    void setCoord(Coordinates& coord);
    std::string getFilePictures();
    int getPictureX();
    int getPictureY();

    /**
     * @brief Return the list of the NPC in the tile, sorted by x-y
     */
    std::list<NPC*>& getNPCs();

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

    /**
     * @brief Returns true if the tile has a texture
     **/
    bool TextureIsInit();
    
    /**
     * @brief Returns true iff the tile is the origin of the building
     **/
    bool isBatOrigin();

    void printTileType();

    /**
     * @brief getNeighbourTiles
     * @return the list of Tiles which can be accesed in one step from this Tile
     * @param map: the map where the Tile is located
     */
    std::list<Tile*> getNeighbourTiles(Geography& map);
    
    /**
     * @brief getNotTooFarNPCs
     * @param map: the map where the Tile is located
     * @return the list of the NPCs around this tile
     */
    std::list<NPC*> getNotTooFarNPCs(Geography& map);

    /**
     * @brief isAligned
     * @param tile1: the first Tile
     * @param tile2: the second Tile
     * @return true iff the Tile is aligned with the 2 other Tiles in this order (tile1,tile2,tile) and they are neighbours
     */
    bool isAligned(Tile& tile1,Tile& tile2); 

    /**
     * @brief Tells if the tile is walkable or not.
     * @return true iff the player can walk on the tile.
     **/
    bool isWalkable();

    /**
     * @brief Tells if the tile is in the fog or not.
     **/
    bool isInFog();

    /**
     * @brief Changes the transparency of the building.
     * Apply changes only to unwalkable buildings.
     **/
    void setAlpha(bool a);
    
    /**
     * @brief Changes the fog state of the building.
     * @param nbFog: the number of hidden tiles of the building.
     * This method is usefull only if the tile is not walkable.
     **/
    void setBuildFog(int nbFog);

    /**
     * @brief Changes the fog state of the tile.
     **/
    void setFog(bool infog);

};





#endif // TILE_H
