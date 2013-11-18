#include <spritelist.h>
#include <SFML/Graphics.hpp>


class SpriteList : public sf::Drawable, public sf::Transformable
{
public:
  void init(const sf::Sprite spr, const SpriteList* list)
  {
    sp = spr;
    li = list;
  }  
  sf::Sprite getSprite()
  {
    return sp;
  }
  SpriteList getTail()
  {
    return li;
  }
private:
  
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    states.transform *= getTransform();

    target.draw(li, states);
    target.draw(sp, states);
  }
  
  sf::Sprite sp;
  SpriteList* li;
};
