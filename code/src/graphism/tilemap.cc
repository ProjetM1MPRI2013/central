#include "tilemap.h"
#include "geography.h"
#include "tile.h"
#include <SFML/Graphics/Transformable.hpp>

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize,
		const int* tiles, unsigned int width, unsigned int height) {
	// on charge la texture du tileset
	if (!m_tileset.loadFromFile(tileset))
		return false;

	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	// on remplit le tableau de vertex, avec un quad par tuile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j) {
			// on récupère le numéro de tuile courant
			int tileNumber = tiles[i + j * width];

			// on en déduit sa position dans la texture du tileset
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			// on récupère un pointeur vers le quad à définir dans le tableau de vertex
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			// on définit ses quatre coins
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j
					* tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1)
					* tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1)
					* tileSize.y);

			// on définit ses quatre coordonnées de texture
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv
					* tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1)
					* tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1)
					* tileSize.y);
		}

	return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// on applique la transformation
	states.transform *= getTransform();

	// on applique la texture du tileset
	states.texture = &m_tileset;

	// et on dessine enfin le tableau de vertex
	target.draw(m_vertices, states);
}


void TileMap::createTiles() {
  unsigned int mapwidth = 100;
  unsigned int mapheight = 100;
  for (unsigned int i = 0; i < mapwidth; ++i) {
    for (unsigned int j = 0; j < mapheight; ++j) {
      switch((geo->getTile(i,j))->getType()) {
      case BLANK:
        Tilesbite[i + j * mapwidth]=0;
        break;
      case ROADV:
        Tilesbite[i + j * mapwidth]=1;
        break;
      case ROADH: 
        Tilesbite[i + j * mapwidth]=2;
        break;
      case INTER:
        Tilesbite[i + j * mapwidth]=3;
        break;
      case HOUSE:
        if ((geo->getTile(i,j))->getAnxiety()<50)
          {Tilesbite[i + j * mapwidth]=4;}
        else {
          if ((geo->getTile(i,j))->getAnxiety()<75)
            {Tilesbite[i + j * mapwidth]=5;}
          else {Tilesbite[i + j * mapwidth]=6;}
        }
        break;
      case BANK:
        if ((geo->getTile(i,j))->getAnxiety()<50) {
          Tilesbite[i + j * mapwidth]=7;
        } else {
          if ((geo->getTile(i,j))->getAnxiety()<75) {
            Tilesbite[i + j * mapwidth]=8;
          } else {
            Tilesbite[i + j * mapwidth]=9;
          }
        } 
        break;
      default:
        break;
      }
    }
  }
  return;
}

TileMap::TileMap(Simulation* simu, Geography* geo){
this->simu=simu;
this->geo=geo;
this->load("../../../sprite/tileset.png", sf::Vector2u(225, 225), Tilesbite , 100, 100);
createTiles();
}

void TileMap::run(sf::RenderWindow* window){
  this->createTiles();
  window->clear();
  window->draw(*this);
  window->display();
}
