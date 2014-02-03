/**
 *@author Denys Kanunikov, others...
 */
#include "simulation.h"
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

#define DEBUG true
#include "debug.h"

Simulation::Simulation(int nbPlayers, int id) {
	this->NB_JOUEURS = nbPlayers;
	//[joseph]map n'est pas définie donc ce qui suit est juste map = map
	//this->map = map;
	//this->oldMap = map;
	this->Id = id;

//	int t[NB_JOUEURS];
//	for (int i = 0; i < NB_JOUEURS; i++) {
//		t[i] = 0;
//	}
	this->mesSous = 0;
	//
	this->sous = std::vector<int>(NB_JOUEURS, 0);
	this->relativeTime = 0;
	this->absoluteTime = 0;
	this->smallTime = 0;

	this->addPlayer(Player(id, 0, 0));

	std::list<NPC*> NPCs;
	this->NPCs = NPCs;
}

Simulation::~Simulation() {

	for (auto& e : NPCs) {
		delete e;
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

Client* Simulation::getClient() {
	assert(client);
	return client;
//  else if (DEBUG) {std::cout << "Client is not initialized!\n"; assert(false)
}

Simulation::Simulation(Geography* map, int nbPlayers, int id) :
		Simulation(nbPlayers, id) {
	this->setGeography(map);
}

/* Never used
 Simulation::Simulation(std::string seed, std::vector<Player *> p_vect)
 : Simulation(p_vect.size(),0) {
 this->setGeography(new Generation1(seed));
 for(Player* p : p_vect)
 this->players.push_back(p);
 }
 */

//void Simulation::setServer(Server* s) {
//    assert(false);
////  this->isServer = true;
////  this->server = s;
////  return;
//}
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
	NPC *npc = new NPC(speed, 10, 10, start, target, *map, tex);
	//on l'ajoute à la liste
	NPCs.push_front(npc);
	//on le met dans sa tile de départ
	npc->getPosition().isInTile(*map).addNPC(npc);

	trigger("NPC::created", *npc);
	return;
}

void Simulation::supprimerNPC(NPC * npc) {
	//on le retire de sa tile
	npc->getPosition().isInTile(*map).removeNPC(npc);
	//on le retire de la liste
	NPCs.remove(npc);
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
	NPCs.remove(npc);
	return;
}

//Crée et tue les gens dans les cases
void Simulation::peopleGeneration() {
	float chance;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			chance = (rand() % 100);

			if (chance > (map->getTile(i, j)->getPopulationDensity() / 10)) {
				int x = rand() % MAP_SIZE;
				int y = rand() % MAP_SIZE;

				while (this->map->getTile(x, y)->getSpeed() == 0) {
					x = rand() % MAP_SIZE;
					y = rand() % MAP_SIZE;
				}

				//addNPC(Position(TILE_SIZE_X * i+ TILE_SIZE_X/2,TILE_SIZE_Y * j+TILE_SIZE_Y /2),Position(x,y),10);
			}
			if (chance < (map->getTile(i, j)->getPopulationDensity() / 10)) {
				supprimerNPCDansCase(i, j);
			}
		}
	}
	return;
}

//Nivelle la peur via une sorte de norme 2
void Simulation::lisserMatrice() {
	float anxiety;
	//float population;
	//Adrien K. : Heuuuuu, ..... je trouve cette ligne bizarre ...
	Geography *oldMap = new Geography;
	*oldMap = *map;
	//interieur de la map
	for (int i = 1; i < MAP_SIZE - 2; i++) {
		for (int j = 1; j < MAP_SIZE - 2; j++) {
			//calcul
			/*anxiety =
			 sqrt2(
			 (1 / 8)
			 * (2 * pow2(oldMap->getAnxiety(i, j), 2)
			 + pow2(oldMap->getAnxiety(i - 1, j),
			 2)
			 + pow2(oldMap->getAnxiety(i, j - 1),
			 2)
			 + pow2(oldMap->getAnxiety(i + 1, j),
			 2)
			 + pow2(oldMap->getAnxiety(i, j + 1),
			 2)
			 + (1 / 2)
			 * (pow2(
			 oldMap->getAnxiety(
			 i - 1,
			 j + 1), 2)
			 + pow2(
			 oldMap->getAnxiety(
			 i
			 + 1,
			 j
			 + 1),
			 2)
			 + pow2(
			 oldMap->getAnxiety(
			 i
			 - 1,
			 j
			 - 1),
			 2)
			 + pow2(
			 oldMap->getAnxiety(
			 i
			 + 1,
			 j
			 - 1),
			 2))));
			 */
			//set
			//Pour l'instant ça pour tester
			anxiety = ((5 * oldMap->getAnxiety(i, j))
					+ oldMap->getAnxiety(i - 1, j)
					+ oldMap->getAnxiety(i + 1, j)
					+ oldMap->getAnxiety(i, j - 1)
					+ oldMap->getAnxiety(i, j + 1)) / 9;
			map->setAnxiety(i, j, anxiety);
		}
	}
	std::cout << "Simulation :fin du centre" << std::endl;

	//bande en bas (i=0)
	for (int j = 1; j < MAP_SIZE - 2; j++) {
		//calcul
		anxiety = sqrt2(
				(1 / 6)
						* (2 * pow2(oldMap->getAnxiety(0, j), 2)
								+ pow2(oldMap->getAnxiety(0, j - 1), 2)
								+ pow2(oldMap->getAnxiety(1, j), 2)
								+ pow2(oldMap->getAnxiety(0, j + 1), 2)
								+ (1 / 2)
										* (pow2(oldMap->getAnxiety(1, j + 1), 2)
												+ pow2(
														oldMap->getAnxiety(1,
																j - 1), 2))));
		//set
		map->setAnxiety(0, j, anxiety);
	}

	//bande à gauche (j=0)
	for (int i = 1; i < MAP_SIZE - 2; i++) {
		//calcul
		anxiety = sqrt2(
				(1 / 6)
						* (2 * pow2(oldMap->getAnxiety(i, 0), 2)
								+ pow2(oldMap->getAnxiety(i - 1, 0), 2)
								+ pow2(oldMap->getAnxiety(i + 1, 0), 2)
								+ pow2(oldMap->getAnxiety(i, 0 + 1), 2)
								+ (1 / 2)
										* (pow2(
												oldMap->getAnxiety(i - 1,
														0 + 1), 2)
												+ pow2(
														oldMap->getAnxiety(
																i + 1, 0 + 1),
														2))));
		//set
		map->setAnxiety(i, 0, anxiety);
	}
	std::cout << "Simulation :fin de la bande gauche" << std::endl;

	//bande à droite (j=MAP_SIZE -1)
	for (int i = 1; i < MAP_SIZE - 2; i++) {
		//calcul
		anxiety =
				sqrt2(
						(1 / 6)
								* (2
										* pow2(
												oldMap->getAnxiety(i,
														MAP_SIZE - 1), 2)
										+ pow2(
												oldMap->getAnxiety(i - 1,
														MAP_SIZE - 1), 2)
										+ pow2(
												oldMap->getAnxiety(i + 1,
														MAP_SIZE - 1), 2)
										+ pow2(
												oldMap->getAnxiety(i,
														MAP_SIZE - 1 - 1), 2)
										+ (1 / 2)
												* (pow2(
														oldMap->getAnxiety(
																i - 1,
																MAP_SIZE - 1
																		- 1), 2)
														+ pow2(
																oldMap->getAnxiety(
																		i + 1,
																		MAP_SIZE
																				- 1
																				- 1),
																2))));
		//set
		map->setAnxiety(i, MAP_SIZE - 1, anxiety);
	}
	std::cout << "Simulation :fin de la bande droite" << std::endl;
	//bande en haut (i=MAP_SIZE -1)
	for (int j = 1; j < MAP_SIZE - 2; j++) {
		//calcul
		anxiety = sqrt2(
				(1 / 6)
						* (2 * pow2(oldMap->getAnxiety(MAP_SIZE - 1, j), 2)
								+ pow2(oldMap->getAnxiety(MAP_SIZE - 2, j), 2)
								+ pow2(oldMap->getAnxiety(MAP_SIZE - 1, j - 1),
										2)
								+ pow2(oldMap->getAnxiety(MAP_SIZE - 1, j + 1),
										2)
								+ (1 / 2)
										* (pow2(
												oldMap->getAnxiety(MAP_SIZE - 2,
														j + 1), 2)
												+ pow2(
														oldMap->getAnxiety(
																MAP_SIZE - 2,
																j - 1), 2))));
		//set
		map->setAnxiety(MAP_SIZE - 1, j, anxiety);
	}
	std::cout << "Simulation :fin de la bande en haut" << std::endl;

	//coin en haut à gauche
	anxiety = sqrt2(
			(1 / 4.5)
					* (2 * pow2(oldMap->getAnxiety(0, MAP_SIZE - 1), 2)
							+ pow2(oldMap->getAnxiety(0, MAP_SIZE - 2), 2)
							+ pow2(oldMap->getAnxiety(1, MAP_SIZE - 1), 2)
							+ (1 / 2)
									* (pow2(oldMap->getAnxiety(1, MAP_SIZE - 2),
											2))));
	map->setAnxiety(0, MAP_SIZE - 1, anxiety);

	//coin en haut à droite
	anxiety = sqrt2(
			(1 / 4.5)
					* (2
							* pow2(
									oldMap->getAnxiety(MAP_SIZE - 1,
											MAP_SIZE - 1), 2)
							+ pow2(
									oldMap->getAnxiety(MAP_SIZE - 1,
											MAP_SIZE - 2), 2)
							+ pow2(
									oldMap->getAnxiety(MAP_SIZE - 2,
											MAP_SIZE - 1), 2)
							+ (1 / 2)
									* (pow2(
											oldMap->getAnxiety(MAP_SIZE - 2,
													MAP_SIZE - 2), 2))));
	map->setAnxiety(MAP_SIZE - 1, MAP_SIZE - 1, anxiety);

	//coin en bas à gauche
	anxiety = sqrt2(
			(1 / 4.5)
					* (2 * pow2(oldMap->getAnxiety(0, 0), 2)
							+ pow2(oldMap->getAnxiety(0, 1), 2)
							+ pow2(oldMap->getAnxiety(1, 0), 2)
							+ (1 / 2) * (pow2(oldMap->getAnxiety(1, 1), 2))));
	map->setAnxiety(0, 0, anxiety);

	//coin en bas à droite
	anxiety = sqrt2(
			(1 / 4.5)
					* (2 * pow2(oldMap->getAnxiety(MAP_SIZE - 1, 0), 2)
							+ pow2(oldMap->getAnxiety(MAP_SIZE - 1, 1), 2)
							+ pow2(oldMap->getAnxiety(MAP_SIZE - 2, 0), 2)
							+ (1 / 2)
									* (pow2(oldMap->getAnxiety(MAP_SIZE - 2, 1),
											2))));
	map->setAnxiety(MAP_SIZE - 1, 0, anxiety);

	std::cout << "fin de tout" << std::endl;
	//delete(oldMap);
	std::cout << "fin du dl" << std::endl;
	return;
}

int Simulation::getSous() {
	return (this->sous[0]);
}

void Simulation::enleveSous(int n) {
	this->sous[0] = this->sous[0] - n;
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
