/**
 *@author Denys Kanunikov, others...
 */
#include "simulation.h"
#include "../graphism/graphic_context_iso.h"
#include "../generation/geography.h"
#include "../generation/tile.h"
#include "npc.h"
#include <cstdlib>
#include <iostream>
#include "position.h"
#include "generation/generation1.h"
#include "network/netEvent.h"
#include "scenario/NewMov.h"
#include "scenario/ScenarioActionList.h"
#include "scenario/HScenario.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#define DEBUG false
#include "debug.h"

Simulation::Simulation(int nbPlayers, int id) :
		scenario(NULL), isServer(false) {
	this->NB_JOUEURS = nbPlayers;
	this->Id = id;

	this->mesSous = 21;
	this->sous = std::vector<int>(NB_JOUEURS, 0);
	this->relativeTime = 0;
	this->absoluteTime = 0;
	this->smallTime = 0;

	DBG << (this->getMap());
	Tile* firstTile = (this->getMap())->getWalkableTile();
	this->addPlayer(
			Player(id, (firstTile->getCoord()).getAbs(),
					(firstTile->getCoord()).getOrd()));

	tmp = std::vector<std::vector<int> >(getMap()->getMapWidth() + 1);
	for (int i = 0; i < getMap()->getMapWidth() + 1; ++i)
		tmp[i] = std::vector<int>(getMap()->getMapWidth() + 1, 0);
}

Simulation::Simulation(Geography* map, int nbPlayers, int id) :
		scenario(NULL), isServer(false) {
	this->setGeography(map);
	this->NB_JOUEURS = nbPlayers;
	this->Id = id;

	this->mesSous = 2;
	this->sous = std::vector<int>(NB_JOUEURS, 200);
	this->relativeTime = 0;
	this->absoluteTime = 0;
	this->smallTime = 0;

	DBG << (this->getMap());
	Tile* firstTile = (this->getMap())->getWalkableTile();
	this->addPlayer(
			Player(id, (firstTile->getCoord()).getAbs(),
					(firstTile->getCoord()).getOrd()));
	tmp = std::vector<std::vector<int> >(getMap()->getMapWidth() + 1);
	for (int i = 0; i < getMap()->getMapWidth() + 1; ++i)
		tmp[i] = std::vector<int>(getMap()->getMapWidth() + 1, 0);
}

Simulation::~Simulation() {

	for (auto& pair : NPCs) {
		delete pair.second;
	}
	NPCs.clear();
	for (auto& e : pendingActions) {
		delete e;
	}
	pendingActions.clear();
	for (auto& e : cameras) {
		delete e;
	}
	cameras.clear();
	for (auto& e : agents) {
		delete e;
	}
	agents.clear();
	sous.clear();
}

void Simulation::setContextIso(GraphicContextIso* gra) {
	this->graContIso = gra;
}

bool Simulation::simIsServer() {
	return isServer;
}

void Simulation::addPlayer(Player&& p) {
	players.push_back(std::move(p));
	return;
}

void Simulation::addAction(ScenarioAction * action) {
	this->pendingActions.push_back(action);
}

Player& Simulation::getPlayerByID(int pid) {
	for (Player& player : players) {
		if (player.getID() == pid) {
			return player;
		}
	}
	throw "getPlayerByID error : Unknown playerID ";
}

Player* Simulation::getPlayer() {
	return &(this->getPlayerByID(this->Id));
}

void Simulation::deleteAction(Action* a) {
	this->toDelete.push_back(a);
	return;
}

//Simplement des casts en float de pow, sqrt et floor
float pow2(float x, float y) {
	return ((float) (pow((double(x)), double(y))));
}

float sqrt2(float x) {
	return ((float) (sqrt((double) x)));
}

float floor2(float x) {
	return ((float) (floor((double(x)))));
}

void Simulation::addNPC(Position start, Position target, float speed,
		TexturePack* tex) {
	//on crée le NPC
	NPC *npc = new NPC(speed, 10, 1.5, start, tex);
	npc->setTarget(target, *map);
	//on l'ajoute à la liste
	NPCs.insert( { npc->getUuid(), npc });
	//on le met dans sa tile de départ
	npc->getPosition().isInTile(*map).addNPC(npc);

	trigger("NPC::created", *npc);
	return;
}

void Simulation::addNPC(Position start, Position target, float speed,
		TexturePack* tex, boost::uuids::uuid id) {
	//on crée le NPC
	NPC *npc = new NPC(speed, 10, 1.5, start, tex, id);
	npc->setTarget(target, *map);
	//on l'ajoute à la liste
	NPCs.insert( { npc->getUuid(), npc });
	//on le met dans sa tile de départ
	npc->getPosition().isInTile(*map).addNPC(npc);
	trigger("NPC::created", *npc);
	return;
}

void Simulation::supprimerNPC(NPC * npc) {
	//on le retire de sa tile
	npc->getPosition().isInTile(*map).removeNPC(npc);
	//on le retire de la liste
	NPCs.erase(npc->getUuid());
	//on le supprime
	delete npc;
	return;
}

void Simulation::supprimerNPCDansCase(int i, int j) {
	//on récupère le 1er NPC de la tile
	NPC *npc = map->getTileRef(i, j).getNPCs().front();
	//on le supprime de la tile
	map->getTileRef(i, j).removeNPC(npc);
	//on le supprime de la liste
	NPCs.erase(npc->getUuid());
	return;
}

/**
 * @brief Simulation::peopleGeneration : Crée et tue les gens dans les cases
 */
void Simulation::peopleGeneration() {
	float chance;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			chance = (rand() % 100);

			if (chance > (map->getTile(i, j)->getPopulationDensity() / 10)) {
				int x = rand() % MAP_SIZE * TILE_SIZE_X;
				int y = rand() % MAP_SIZE * TILE_SIZE_Y;

				while (this->map->getTile(x, y)->getSpeed() == 0) {
					x = rand() % MAP_SIZE * TILE_SIZE_X;
					y = rand() % MAP_SIZE * TILE_SIZE_Y;
				}

				std::cout << "npc created, target =  (" << x << "," << y << ")"
						<< std::endl;

				this->addNPC(
						Position(TILE_SIZE_X * i + TILE_SIZE_X / 2,
								TILE_SIZE_Y * j + TILE_SIZE_Y / 2),
						Position(x, y), 1,
						this->graContIso->getTexturePack(i % 2));

				//addNPC(Position(TILE_SIZE_X * i+ TILE_SIZE_X/2,TILE_SIZE_Y * j+TILE_SIZE_Y /2),Position(x,y),10);
			}
			if (chance < (map->getTile(i, j)->getPopulationDensity() / 10)) {
				supprimerNPCDansCase(i, j);
			}
		}
	}
	return;
}

void Simulation::reroute(NPC& npc) {
	int x = rand() % MAP_SIZE;
	int y = rand() % MAP_SIZE;
	while (this->map->getTile(x, y)->getSpeed() == 0) {
		x = rand() % MAP_SIZE;
		y = rand() % MAP_SIZE;
	}
	npc.setTarget(Position(x, y), *(this->map));
	return;
}

void Simulation::copyTmp() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			tmp[i][j] = this->map->getAnxiety(i, j);
		}
	}
}

/**
 * @brief Simulation::lisserMatrice : Nivelle la peur via une sorte de norme 2
 */
void Simulation::lisserMatrice() {
	float anxiety;

	//on met les valeurs courantes de la geography dans une matrice de chiffres (attribut de simulation)
	this->copyTmp();

	//interieur de la map
	for (int i = 1; i < MAP_SIZE - 2; i++) {
		for (int j = 1; j < MAP_SIZE - 2; j++) {
			//calcul
			//set
			//Pour l'instant ça pour tester
			anxiety = ((5 * tmp[i][j]) + tmp[i - 1][j] + tmp[i + 1][j]
					+ tmp[i][j - 1] + tmp[i][j + 1]) / 9;
			map->setAnxiety(i, j, anxiety);
		}
	}
	DBG << "Simulation :fin du centre";

	//bande en bas (i=0)
	for (int j = 1; j < MAP_SIZE - 2; j++) {
		//calcul
		anxiety = sqrt2(
				(1 / 6)
						* (2 * pow2(tmp[0][j], 2) + pow2(tmp[0][j - 1], 2)
								+ pow2(tmp[1][j], 2) + pow2(tmp[0][j + 1], 2)
								+ (1 / 2)
										* (pow2(tmp[1][j + 1], 2)
												+ pow2(tmp[1][j - 1], 2))));
		//set
		map->setAnxiety(0, j, anxiety);
	}

	//bande à gauche (j=0)
	for (int i = 1; i < MAP_SIZE - 2; i++) {
		//calcul
		anxiety = sqrt2(
				(1 / 6)
						* (2 * pow2(tmp[i][0], 2) + pow2(tmp[i - 1][0], 2)
								+ pow2(tmp[i + 1][0], 2)
								+ pow2(tmp[i][0 + 1], 2)
								+ (1 / 2)
										* (pow2(tmp[i - 1][1], 2)
												+ pow2(tmp[i + 1][1], 2))));
		//set
		map->setAnxiety(i, 0, anxiety);
	}
	DBG << "Simulation :fin de la bande gauche";

	//bande à droite (j=MAP_SIZE -1)
	for (int i = 1; i < MAP_SIZE - 2; i++) {
		//calcul
		anxiety = sqrt2(
				(1 / 6)
						* (2 * pow2(tmp[i][MAP_SIZE - 1], 2)
								+ pow2(tmp[i - 1][MAP_SIZE - 1], 2)
								+ pow2(tmp[i + 1][MAP_SIZE - 1], 2)
								+ pow2(tmp[i][MAP_SIZE - 1 - 1], 2)
								+ (1 / 2)
										* (pow2(tmp[i - 1][MAP_SIZE - 1 - 1], 2)
												+ pow2(
														tmp[i + 1][MAP_SIZE - 1
																- 1], 2))));
		//set
		map->setAnxiety(i, MAP_SIZE - 1, anxiety);
	}
	DBG << "Simulation :fin de la bande droite";
	//bande en haut (i=MAP_SIZE -1)
	for (int j = 1; j < MAP_SIZE - 2; j++) {
		//calcul
		anxiety = sqrt2(
				(1 / 6)
						* (2 * pow2(tmp[MAP_SIZE - 1][j], 2)
								+ pow2(tmp[MAP_SIZE - 2][j], 2)
								+ pow2(tmp[MAP_SIZE - 1][j - 1], 2)
								+ pow2(tmp[MAP_SIZE - 1][j + 1], 2)
								+ (1 / 2)
										* (pow2(tmp[MAP_SIZE - 2][j + 1], 2)
												+ pow2(tmp[MAP_SIZE - 2][j - 1],
														2))));
		//set
		map->setAnxiety(MAP_SIZE - 1, j, anxiety);
	}
	DBG << "Simulation :fin de la bande en haut";

	//coin en haut à gauche
	anxiety = sqrt2(
			(1 / 4.5)
					* (2 * pow2(tmp[0][MAP_SIZE - 1], 2)
							+ pow2(tmp[0][MAP_SIZE - 2], 2)
							+ pow2(tmp[1][MAP_SIZE - 1], 2)
							+ (1 / 2) * pow2(tmp[1][MAP_SIZE - 2], 2)));
	map->setAnxiety(0, MAP_SIZE - 1, anxiety);

	//coin en haut à droite
	anxiety =
			sqrt2(
					(1 / 4.5)
							* (2 * pow2(tmp[MAP_SIZE - 1][MAP_SIZE - 1], 2)
									+ pow2(tmp[MAP_SIZE - 1][MAP_SIZE - 2], 2)
									+ pow2(tmp[MAP_SIZE - 2][MAP_SIZE - 1], 2)
									+ (1 / 2)
											* (pow2(
													tmp[MAP_SIZE - 2][MAP_SIZE
															- 2], 2))));
	map->setAnxiety(MAP_SIZE - 1, MAP_SIZE - 1, anxiety);

	//coin en bas à gauche
	anxiety =
			sqrt2(
					(1 / 4.5)
							* (2 * pow2(tmp[0][0], 2) + pow2(tmp[0][1], 2)
									+ pow2(tmp[1][0], 2)
									+ (1 / 2) * pow2(tmp[1][1], 2)));
	map->setAnxiety(0, 0, anxiety);

	//coin en bas à droite
	anxiety = sqrt2(
			(1 / 4.5)
					* (2 * pow2(tmp[MAP_SIZE - 1][0], 2)
							+ pow2(tmp[MAP_SIZE - 1][1], 2)
							+ pow2(tmp[MAP_SIZE - 2][0], 2)
							+ (1 / 2) * (pow2(tmp[MAP_SIZE - 2][1], 2))));
	map->setAnxiety(MAP_SIZE - 1, 0, anxiety);

	DBG << "fin de tout";
	DBG << "fin du dl";
	return;
}

int Simulation::getSous() {
	return (this->mesSous);
}

void Simulation::enleveSous(int n) {
	this->mesSous = this->mesSous - n;
	std::cout << "ok" << std::endl;
	return;
}

void Simulation::addAgent(Agent* agent) {
	agents.push_back(agent);
	return;
}

void Simulation::addCam(Camera* cam) {
	cameras.push_back(cam);
	return;
}

void Simulation::setGeography(Geography *g) {
	map = g;
	if (map) {
		MAP_SIZE = map->getMapWidth();
	}
	return;
}

void Simulation::setScenario(HScenario* s) {
	scenario = s;
	return;
}

NPC* Simulation::getNPCByID(boost::uuids::uuid uuid) {
	auto iterator = NPCs.find(uuid);
	return (iterator == NPCs.end()) ? nullptr : (iterator->second);
}
