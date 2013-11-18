#ifndef SPLIST
#define SPLIST

#include <SFML/Graphics.hpp>

/**
 * @brief list of Sprites
 * Define a drawing priority order over a set of sprites
 * The head of the list must be drawn over the others
 * It is typically used to draw a tile of the map with multiples npcs overlaping each other, on top of the prite of the road.
 * It also allows individual transformations such as transparency for buildings.
 * This list must be computed at each iteration of the draw function because drawing priority may change from one frame to another
 */
class SpriteList : public sf::Drawable, public sf::Transformable
{
 public:
  /**
   * @brief init
   * Builds a list
   */
  void init(const sf::Sprite spr, const SpriteList* list);
  /**
   * @brief getSprite
   */
  sf::Sprite getSprite();
  /**
   * @brief getTail
   */
  SpriteList getTail();
 private:
  /**
   * @brief draw
   * Draws the sprites in a specific order
   */
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  /**
   * @brief head
   */
  sf::Sprite sp;
  /**
   * @brief tail
   */
  SpriteList* li;
};


#endif
