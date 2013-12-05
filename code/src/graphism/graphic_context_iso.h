#ifndef GRAPHICCONTEXT
#define GRAPHICCONTEXT

#include <SFML/Graphics.hpp>
#include <vector>
#include "animation.h"          // TexturePack
#include "../generation/tile.h" // SpriteTilePack
#include "../generation/geography.h"

#define OFFSET_Y 1000                     /* Pour toujours avoir des images dans un cadre positif */
#define OFFSET_X 1000
#define RIGHT_TILE(x) ((x==0) ? 20 : -10) /* Distance à la tile de droite */
#define DOWN_TILE(x) ((x==0) ? 20 : 10)   /* Distance à la tile du bas */

/**
  * @brief GraphicContextIso
  * This class contains all the textures of the isometric view
  * It is initially loaded at the beginning of the main loop, and should not be destructed
  * draw is called to draw the map on a sf::RenderTarget such as the main window
  **/

class GraphicContextIso : public sf::Drawable, public sf::Transformable {

 public: 
  /**
    * @brief Constructor of the GraphicContextIso class
    * @param map: the map that should be drawn
    * This function loads all the textures and keeps a pointer to the map for a further rendition
    **/
  GraphicContextIso(Geography* map); 
  
  /**
    * @brief draw
    * Draws the map
    * @param target: the target where the map have to be drawn at
    * @param states: transformations applied to the map
    **/
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
  
  void addTexturePack(TexturePack t);

  void addSpriteTilePack(SpriteTilePack stp);

 private:
  std::vector<TexturePack> texVector;
  std::vector<SpriteTilePack> tilepackVector;
  Geography* map;
   
};

#endif
