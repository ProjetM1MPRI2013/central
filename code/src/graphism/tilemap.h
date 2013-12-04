#ifndef TILEMAP
#define TILEMAP
class TileMap : public sf::Drawable, public sf::Transformable
{
public:

  bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  int* createTiles(Geography map); 
}
?
