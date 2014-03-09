/**
 *@author Denys KANUNIKOV,Marc B
 */
#include "localState.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include "network/netEvent.h"
#include "scenario/NewMov.h"
#include "scenario/ScenarioActionList.h"
#include "scenario/HScenario.h"

#define DEBUG false

#include "debug.h"

/**
 * @brief LocalState::LocalState
 * @param map: the map which is used by the LocalState.
 * @param nbPlayers: number of players in the game
 * @param id:  id of the player to whom the state belongs
 */
LocalState::LocalState(Geography* map, int nbPlayers, int id) :
		Simulation(map, nbPlayers, id), client(NULL), owner_player(
				getPlayerByID(id)) {
	isServer = false;
}

/**
 * @brief LocalState::getLocalTime
 * @return link to a local time of the state
 */
sf::Time &LocalState::getLocalTime() {
	return localtime;
}

/**
 * @brief LocalState::getRelativePlayerTile
 * @param x : number of tiles to the right from the players position
 * @param y : number of tiles to the top from the players position
 * @return a reference to a Tile if on map, or owner's tile otherwise
 */
Tile& LocalState::getRelativePlayerTile(int x, int y) {
	int absciss = owner_player.getPosition().isInTile(*map).getCoord().getAbs();
	int ordinate =
			owner_player.getPosition().isInTile(*map).getCoord().getOrd();
	absciss += x;
	ordinate += y;
	if ((absciss < map->getMapWidth()) && (absciss >= 0)
			&& (ordinate < map->getMapHeight()) && (ordinate >= 0)) {
		return map->getTileRef(absciss, ordinate);
	} else {
		return owner_player.getPosition().isInTile(*map);
	}
}

/**
 * @brief LocalState::getOwner
 * @return  reference to the owner
 */
Player& LocalState::getOwner() {
	return owner_player;
}

/**
 * @brief LocalState::getTile
 * @param p: position
 * @return a reference to a Tile of the LocalState map
 */
Tile& LocalState::getTile(Position p) {
	return p.isInTile(*map);
}

//Nobody je rajoute ça :
/**
 * @brief LocalState::getCurrentTile
 * @return a pair<int,int> of Coordinates of the Player
 */
std::pair<int, int> LocalState::getCurrentTile() {
	Player* p = this->getPlayer();
	Position& pos = p->getPosition();
	Geography* map = this->getMap();
	Tile& t = pos.isInTile(*map);
	std::pair<int, int> pr(t.getCoord().abs, t.getCoord().ord);
	return pr;
}

void LocalState::run(sf::Time dt) {
	//If teir is no enough money, remove an agent and a camera
	//The client retrieve all the new messages from the network (of type ScenarioAction), and add them to the list of pending ScenarioAction
	std::vector<ScenarioAction *> scenarioActionFromNetwork =
			this->client->receiveMessages<ScenarioAction>();
	for (ScenarioAction* action : scenarioActionFromNetwork) {
		DBG << "Client : add a ScenarioAction from network of type "
				<< action->name;
		action->simulation = this;
		this->addAction(action);
	}

	for (ScenarioAction* action : pendingActions) {
		std::cout << "Client : applying pending Scenario Action of type "
				<< action->name << std::endl;
		action->run();
		std::cout << "nobody client fin run " << std::endl;
	}

  
  auto npcUpdates = client->receiveMessages<NpcUpdate>();
  for (NpcUpdate* update : npcUpdates) {
    if (update->isCreated) {
      NPC* npc = update->createNpc();
      npc->setTarget(update->target,*map);
      addNPC(npc);
    } else {
      NPC* npc = getNPCByID(update->id);
      if (npc == nullptr) {
        throw std::runtime_error("Received network information about nonexistent NPC (maybe we don't care)");
      } else {

        if (!(npc->getTarget().equal(update->target))) {
          npc->setTarget(update->target, *map);
        }

        Tile& tileBefore = npc->getPosition().isInTile(*map);
        update->updateNpc(*npc);
        Tile& tileAfter = npc->getPosition().isInTile(*map);

        if (!tileBefore.equals(tileAfter)) {
          tileBefore.removeNPC(npc);
          tileAfter.addNPC(npc);
        }

      }
    }
  }


	this->pendingActions.clear();
	//On supprime les actions déjà traitées
	this->toDelete.clear();
	/*on empile les dt jusqu'à obtenir plus d'une seconde*/
	this->smallTime = smallTime + dt.asSeconds();
	/*on compte le nombre de secondes dans dt*/
	int secondes = floor(smallTime);
	smallTime = smallTime - secondes;
	/* We update the position of all the players */
	for (Player& player : players)
		player.updatePosition(dt, *map);
	/*on n'effectue pas le lissage de la matrice plus d'une fois par seconde*/
	for (int i = 0; i < secondes; i++)
		this->lisserMatrice();
	/*on fait payer l'entretien des différents trucs*/
	for (int i = 0; i < secondes; i++) {
		for (Agent* agent : agents) {
			mesSous = mesSous - (i+1)*agent->getEntretien();
		}
		for (Camera* camera : cameras) {
			mesSous = mesSous - (i+1)*camera->getEntretien();
		}
		mesSous = mesSous + (i+1)*10;
	}
	if (mesSous < 0) {
			if (!(this->agents.empty())) {
				this->agents.pop_back();
			}
			if (!(this->cameras.empty())) {
				this->cameras.pop_back();
			}
		}

	DBG << "LocalState : Position of the Player" << getOwner().getPosition();
	client->update(dt);
	return;
}
/**
 * @brief LocalState::setClient setting a network client for the local state.
 * After this step we can opereate over the network
 * @param c : client
 */
void LocalState::setClient(Client* c) {
	client = c;
	c->setLocalState(this);
	return;
}

/**
 * @brief LocalState::getClient
 * @return a pointer to the client of the LocalState
 */
Client* LocalState::getClient() {
	return client;
}

