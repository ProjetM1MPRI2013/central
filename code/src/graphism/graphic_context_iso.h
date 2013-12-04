#ifndef GRAPHICCONTEXT
#define GRAPHICCONTEXT

#include <SFML/Graphics.hpp>
#include "animation.h"          // TexturePack
#include "../generation/tile.h" // SpriteTilePack
#include "../generation/geography.h"

#define OFFSET_Y 1000
#define OFFSET_X 1000
#define RIGHT_TILE {20;-10} /* Distance à la tile de droite */
#define DOWN_TILE {20;10} /* Distance à la tile du bas */

class GraphicContextIso : public sf::Drawable, public sf:Transformable {

 public: 

  GraphicContext(Geography* map); 
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
 private:
  TexturePack* texArray;
  SpriteTilePack* tilepackArray;
  Geography* map;
   
}

#endif