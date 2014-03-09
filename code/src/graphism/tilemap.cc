#include "tilemap.h"
#include "geography.h"
#include "tile.h"
#include <SFML/Graphics/Transformable.hpp>

#define DEBUG false
#include "debug.h"

int TileMap::getZoom() {
	return this->zoom;
}

void TileMap::setZoom(int resize) {
	this->zoom = resize;
}

bool TileMap::load(const std::string& tileset1, const std::string& tileset2,
		sf::Vector2u tileSize, const int* tiles, unsigned int width,
		unsigned int height) {
	// on charge la texture du tileset
	if (!m_tileset_anxiety.loadFromFile(tileset1)) {
		LOG(error)<< "Could not load tileset " << tileset1; exit(1);
	}

	if (!m_tileset_population.loadFromFile(tileset2)) {
		LOG(error)<< "Could not load tileset " << tileset2; exit(1);
	}

	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	// on remplit le tableau de vertex, avec un quad par tuile
	for (unsigned int i = x; i < width; ++i)
	for (unsigned int j = y; j < height; ++j) {
		// on récupère le numéro de tuile courant
		int tileNumber = tiles[i + j * width];

		int tu(0),tv(0);

		if(pop) {
			// on en déduit sa position dans la texture du tileset
			tu = tileNumber % (m_tileset_population.getSize().x / 78);
			tv = tileNumber / (m_tileset_population.getSize().x / 78);
			//std::cout<<" tu= " << tu << " tv= " << tv << std::endl;
		}
		else {
			tu = tileNumber % (m_tileset_anxiety.getSize().x / 78);
			tv = tileNumber / (m_tileset_anxiety.getSize().x / 78);
		}

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
		quad[0].texCoords = sf::Vector2f(tu * 78, tv * 78);
		quad[1].texCoords = sf::Vector2f((tu + 1) * 78, tv
				* tileSize.y);
		quad[2].texCoords = sf::Vector2f((tu + 1) * 78, (tv + 1)
				* tileSize.y);
		quad[3].texCoords = sf::Vector2f(tu * 78, (tv + 1)
				* tileSize.y);
	}
	return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// on applique la transformation
	states.transform *= getTransform();

	// on applique la texture du tileset
	if (!pop) {
		states.texture = &m_tileset_anxiety;
	} else {
		states.texture = &m_tileset_population;
	}

	// et on dessine enfin le tableau de vertex
	target.draw(m_vertices, states);
}

//choice = true si anxiety, false si population
void TileMap::createTiles() {
	unsigned int mapwidth = 100;
	unsigned int mapheight = 100;

	if (!pop) {

		for (unsigned int i = 0; i < mapwidth; ++i) {
			for (unsigned int j = 0; j < mapheight; ++j) {
				switch ((geo->getTile(i, j))->getType()) {
				case BLANK:
					Tilesbite[i + j * mapwidth] = 0;
					break;
				case ROADV:
					Tilesbite[i + j * mapwidth] = 2; //that's cool
					break;
				case ROADH:
					Tilesbite[i + j * mapwidth] = 1; //that's cool
					break;
				case INTER:
					Tilesbite[i + j * mapwidth] = 3;
					break;
				case HOUSE:
					if ((geo->getTile(i, j))->getAnxiety() < 50) {
						Tilesbite[i + j * mapwidth] = 4;
					} else {
						if ((geo->getTile(i, j))->getAnxiety() < 75) {
							Tilesbite[i + j * mapwidth] = 5;
						} else {
							Tilesbite[i + j * mapwidth] = 6;
						}
					}
					break;
				case BANK:
					if ((geo->getTile(i, j))->getAnxiety() < 50) {
						Tilesbite[i + j * mapwidth] = 7;
					} else {
						if ((geo->getTile(i, j))->getAnxiety() < 75) {
							Tilesbite[i + j * mapwidth] = 8;
						} else {
							Tilesbite[i + j * mapwidth] = 9;
						}
					}
					break;
				default:
					break;
				}
			}
		}

	} else {
		/*
		 for (unsigned int i = 0; i < mapwidth; ++i) {
		 for (unsigned int j = 0; j < mapheight; ++j) {
		 if ((geo->getTile(i, j))->getPopulationDensity() < 20) {
		 Tilesbite[i + j * mapwidth] = 4;
		 } else {
		 if ((geo->getTile(i, j))->getPopulationDensity() < 60) {
		 Tilesbite[i + j * mapwidth] = 5;
		 } else {
		 Tilesbite[i + j * mapwidth] = 6;
		 }
		 }
		 }
		 }*/

		for (unsigned int i = 0; i < mapwidth; ++i) {
			for (unsigned int j = 0; j < mapheight; ++j) {
				switch ((geo->getTile(i, j))->getType()) {
				case BLANK:
					if ((geo->getTile(i, j))->getPopulationDensity() < 20) {
						Tilesbite[i + j * mapwidth] = 4;
					} else {
						if ((geo->getTile(i, j))->getPopulationDensity() < 60) {
							Tilesbite[i + j * mapwidth] = 5;
						} else {
							Tilesbite[i + j * mapwidth] = 6;
						}
					}
					break;
				case ROADV:
					Tilesbite[i + j * mapwidth] = 2;
					break;
				case ROADH:
					Tilesbite[i + j * mapwidth] = 1;
					break;
				case INTER:
					Tilesbite[i + j * mapwidth] = 3;
					break;
				case HOUSE:
					if ((geo->getTile(i, j))->getPopulationDensity() < 20) {
						Tilesbite[i + j * mapwidth] = 4;
					} else {
						if ((geo->getTile(i, j))->getPopulationDensity() < 60) {
							Tilesbite[i + j * mapwidth] = 5;
						} else {
							Tilesbite[i + j * mapwidth] = 6;
						}
					}
					break;
				case BANK:
					if ((geo->getTile(i, j))->getPopulationDensity() < 20) {
						Tilesbite[i + j * mapwidth] = 7;
					} else {
						if ((geo->getTile(i, j))->getPopulationDensity() < 60) {
							Tilesbite[i + j * mapwidth] = 8;
						} else {
							Tilesbite[i + j * mapwidth] = 9;
						}
					}
					break;
				default:
					break;
				}
			}
		}

	}
	return;
}

void TileMap::setCoord(int x, int y) {
	this->x = x;
	this->y = y;
}

int TileMap::getX() {
	return this->x;
}

int TileMap::getY() {
	return this->y;
}

TileMap::TileMap(Simulation* _simul, Geography* geo) {
	simul_state = _simul;
	this->geo = geo;
	this->zoom = 1;
	this->load("../../../sprite/tileset.png", "../../../sprite/tileset2Pop.png",
			sf::Vector2u(10, 10), Tilesbite, 100, 100);
	createTiles();
}

void TileMap::changeView() {
	this->pop = not pop;
	return;
}

void TileMap::run(sf::RenderWindow* window) {
	this->createTiles();
	//aide au débuggage
	//for (int i = 0; i < 100; i++) {
	//	for (int j = 0; j < 100; j++) {
	//		std::cout << (Tilesbite[i + j * 100]) << "\t";
	//	}
	//	std::cout << std::endl;
	//};

	//std::cout << "zoom : " << this->zoom << std::endl;
	this->load("../../../sprite/tileset2.png",
			"../../../sprite/tileset2Pop.png",
			sf::Vector2u((this->zoom) * 20, (this->zoom) * 20), Tilesbite, 100,
			100);
	//createTiles();
	window->draw(*this);
}


Position TileMap::CoordMouse(sf::Vector2i Coord){
	float X = ((float)Coord.x)/(zoom*78) + ((float)TileMap::getX()) ;
	float Y = ((float)Coord.y)/(zoom*78)+((float)TileMap::getY()) ;
	std::cout << X << "\t";
	std::cout << Y << "\t";
	Position pos = Position(X,Y);
	return pos;
}

void TileMap::newMovement(NewMov mov,Simulation& s){

					int x=TileMap::getX();
					int y=TileMap::getY();
			switch (mov) {
			case NewMov::P_UP:
				if (x>0) {TileMap::setCoord(x-1,y);
				};
				break;
			case NewMov::P_LEFT:
				if (y>0) {TileMap::setCoord(x,y-1);
				};
				break;
			case NewMov::P_DOWN:
				if (x<100) {TileMap::setCoord(x+1,y);
				};
				break;
			case NewMov::P_RIGHT:
				if (y<100) {TileMap::setCoord(x,y+1);
				};
				break;
			default:
				break;
			};
}
