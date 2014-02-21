/**
 * @author: MrKulu
 */
#ifndef GRAPHICCONTEXT
#define GRAPHICCONTEXT

#include <SFML/Graphics.hpp>
#include <vector>
#include "eventListener.h"
#include "animation.h"          // TexturePack
#include "../generation/tile.h" // SpriteTilePack
#include "game_textures.h"
#include "../generation/geography.h"
#include "../simulation/simulation.h"
#include "../simulation/position.h"
#include "../simulation/positionable.h"
#include <unordered_map>

#define OFFSET_Y 1000                     /* Pour toujours avoir des images dans un cadre positif */
#define OFFSET_X 1000
#define RIGHT_TILE(x) ((x==0) ? 20 : -10) /* Distance à la tile de droite */
#define DOWN_TILE(x) ((x==0) ? 20 : 10)   /* Distance à la tile du bas */

/**
 * @brief This class contains all the textures of the isometric view.
 * It is initially loaded at the beginning of the main loop, and should not be destructed.
 * draw is called to draw the map on a sf::RenderTarget such as the main window.
 **/

class GraphicContextIso : public sf::Drawable, public sf::Transformable, public EventListener<GraphicContextIso> {

 public: 
  /**
    * @brief Constructor of the GraphicContextIso class.
    * @param map: the map that should be drawn;
    * @param sim: the simulation.
    * This function loads all the textures and keeps a pointer to the map for a further rendition.
    **/
  GraphicContextIso(Geography* map, Simulation* sim); 
  
  /**
    * @brief Draws the map.
    * @param target: the target where the map have to be drawn at;
    * @param states: transformations applied to the map.
    **/
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
  /**
   * @brief Add a texture Pack for a DrawableObject
   **/  
  void addTexturePack(TexturePack t);

  /**
   * @brief Runs one computation of the graphical output of the map.
   **/
  void run(sf::RenderWindow* window);

  /**
   * @brief Returns the position on the map of the pixel (x,y).
   * Can have negative coordinates.
   * Assumes the view fills the window.
   **/
  Position screenToMap(int x, int y);

  /**
   * @brief Changes the zoom of the view.
   **/
  float zoom(float f);

  /**
   * @brief Adds an object that reveals a part of the map
   **/
  void addUnfog(Positionable* p, int radius);

  /**
   * @brief A method to update the fog
   * It is not used outside of the class
   **/
  void updateFog(Coordinates c, int r, int modif);
  
  /**
   * @brief Update the fog whenever a listened Positionable changes it's position
   **/
  void changedTile(Positionable& p, std::pair<Coordinates,Coordinates> modifpos);
  

 private:
  std::unordered_map<std::string, SpriteTilePack> tilemap;
  Geography* map;
  Simulation* sim;
  sf::View view;
  float zoomfactor;
  float zoommax;
  float zoommin;
  sf::Texture fogT;
  sf::Texture baseT;
  std::list<Tile*> drawList;
  sf::Clock spf;
  sf::Font dafont;
  std::list<Positionable*> unfogVector;

  sf::Texture playerT;
 
};

#endif
