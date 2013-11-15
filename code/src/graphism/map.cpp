#include <SFML/Graphics.hpp>
#include <simulation/localState.h>
#include <simulation/geography.h>


class Sprite :
{
public:
  int getHeight()
  { return height };
  int getWidth()
  { return width };
  coord getTile()
  { return c_tileset };
  coord getMap()
  { return c_map };  
  void setHeight(int h)
  { height = h };
  void setWidth(int w)
  {width = w};
  void setTile(coord ct)
  {c_tileset = ct};
  void setMap(coord cm)
  {c_map = cm};
private:
  int height, width;
  coord c_tileset, c_map; 
};

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, const Geography map)
    {
      int width = MAX_SIZE, heigth = MAX_SIZE, trans_height = -MAX_SIZE*RIGHT_TILE[1];  

      // on charge la texture du tileset
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int i = 0; i < width; ++i)
	  for (unsigned int j = 0; j < height; ++j)
            {
	      // on récupère le numéro de tuile courant
	      Terrain tile = map.getTile(i,j);

	      sprite = tile.getSprite();
	      
	      // on en extrait sa position dans la texture du tileset
	      int tu = (sprite.getTile()).x;
	      int tv = (sprite.getTile()).y;
	      int th = sprite.getHeight();
	      int tw = sprite.getWidth();

	      int tmu = (sprite.getMap()).x;
	      int tmv = (sprite.getMap()).y;

	      // on récupère un pointeur vers le quad à définir dans le tableau de vertex
	      sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // on définit ses quatre coins
	      quad[0].position = sf::Vector2f(i * RIGHT_TILE[0] + j * DOWN_TILE[0] - tmu, i * RIGHT_TILE[1] + j * SIZE_TILE[1] - tmv);
	      quad[1].position = sf::Vector2f(i * RIGHT_TILE[0] + j * DOWN_TILE[0] - tmu + tw , i * RIGHT_TILE[1] + j * SIZE_TILE[1] - tmv);
	      quad[2].position = sf::Vector2f(i * RIGHT_TILE[0] + j * DOWN_TILE[0] - tmu + tw, i * RIGHT_TILE[1] + j * SIZE_TILE[1] - tmv + th);
	      quad[3].position = sf::Vector2f(i * RIGHT_TILE[0] + j * DOWN_TILE[0] - tmu, i * RIGHT_TILE[1] + j * SIZE_TILE[1] - tmv + th);

                // on définit ses quatre coordonnées de texture
	      quad[0].texCoords = sf::Vector2f(tu, tv);
	      quad[1].texCoords = sf::Vector2f(tu + tw, tv);
	      quad[2].texCoords = sf::Vector2f(tu + tw, tv + th);
	      quad[3].texCoords = sf::Vector2f(tu, tv + th);
            }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};
