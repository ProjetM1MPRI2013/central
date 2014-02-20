/**
 *@author Denys KANUNIKOV,
 */
#include "globalState.h"
#include "network/netEvent.h"
#include "scenario/NewMov.h"
#include "scenario/ScenarioActionList.h"
#include "scenario/HScenario.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#define DEBUG false

#include "debug.h"

GlobalState::GlobalState(Geography* map, int nbPlayers, int id) :
		Simulation(map, nbPlayers, id), server(NULL) {
	isServer = true;
}

void GlobalState::setServer(Server *_server) {
	server = _server;
	server->setSimulation(this);
}

void GlobalState::run(sf::Time dt) {
	//If their is no enough money, remove an agent and a camera
	if (sous[0] < 0) {
		if (!this->agents.empty()) {
			this->agents.pop_back();
		}
		if (!this->cameras.empty()) {
			this->cameras.pop_back();
		}
	}

	/**The server retrieve all the new messages from the network (of type Action),
	 *turn them into ScenarioAction, and add those ScenarioAction to the list of
	 *pending ScenarioAction
	 */
	std::vector<Action *> actionFromNetwork = server->receiveMessages<Action>();

	for (Action * action : actionFromNetwork) {
		action->addPendingActions(this);
		DBG << "Host : new Action from network of type " << action->name;
	}
	actionFromNetwork.clear();

	/**The server retrieve all the new messages from the network
	 *(of type NewMovNetwork), turn them into ScenarioAction,
	 *and add those ScenarioAction to the list of pending ScenarioAction
	 */
	std::vector<NewMovNetwork *> movFromNetwork = server->receiveMessages<
			NewMovNetwork>();

	for (NewMovNetwork * newMove : movFromNetwork) {
		this->addAction(
				(ScenarioAction *) new ChangeDirection(newMove->playerID,
						newMove->newDirection, newMove->timeStamp, this));
		DBG << "Host : New Movement from player : " << newMove->playerID;
	}
	movFromNetwork.clear();

	/**The server retrieve all the new messages from the network
	 *(of type NewMouseMovNetwork), turn them into ScenarioAction,
	 *and add those ScenarioAction to the list of pending ScenarioAction
	 */
	std::vector<NewMouseMovNetwork *> mouseMovFromNetwork =
			server->receiveMessages<NewMouseMovNetwork>();

	for (NewMouseMovNetwork * newMouseMove : mouseMovFromNetwork) {
		this->addAction(
				(ScenarioAction *) new ChangeDestination(newMouseMove->playerID,
						newMouseMove->destination, newMouseMove->timeStamp,
						this));
		DBG << "Host : New Mouse Movement from player : "
				<< newMouseMove->playerID;
	}

	mouseMovFromNetwork.clear();

	for (ScenarioAction* action : pendingActions) {
		//The server sends the ScenarioAction to the client, so they can do them.
		DBG << "Host : applying pending Scenario Action of type "
				<< action->name;
		if (action->name != "ChangeDirection"
				&& action->name != "ChangeDestination") {
			DBG << "Host : sending the action to the network";
			server->broadcastMessage(*action, true);
		}
		DBG << "Nobody : serveur run action";
		action->run();
		DBG << " Nobody :serveur fin run action";
	}
	pendingActions.clear();

	//On supprime les actions déjà traitées
	toDelete.clear();

	/*on empile les dt jusqu'à obtenir plus d'une seconde*/
	smallTime = smallTime + dt.asSeconds();

	/*on compte le nombre de secondes dans dt*/
	int secondes = floor(smallTime);
	smallTime = smallTime - secondes;

	DBG << "on lisse la matrice ";

	//Si ça fait plus d'une seconde, on fait changer de direction les gens qui ont peur
	if (secondes > 0) {
		for (NPC* npc : NPCs) {
			if (npc->isShocked()) {
				this->reroute(*npc);
			}
		}
	}

	/*on n'effectue pas le lissage de la matrice plus d'une fois par seconde*/
	for (int i = 0; i < secondes; i++) {
		this->lisserMatrice();
	}
	/* We update the position of all the players */
	for (Player& player : players) {
		player.updatePosition(dt, *map);
	}

	/*on fait payer l'entretien des différents trucs*/
	for (int i = 1; i < secondes; i++) {
		for (Agent* agent : agents) {
			sous[0] = sous[0] - agent->getEntretien();
		}

		for (auto camera : cameras) {
			sous[0] = sous[0] - camera->getEntretien();
		}
	}

	//Deplacement de tous les NPCs.
	DBG << "on commence à bouger les npcs";
	for (NPC* npc : NPCs) {
		bool wasArrived = npc->hasArrived();
		Tile& tileBefore = npc->getPosition().isInTile(*map);
		npc->updatePosition(dt, *map);
		Tile& tileAfter = npc->getPosition().isInTile(*map);
		if (!tileBefore.equals(tileAfter)) {
			/*
			 * To listen with class C, derive EventListener<C> and then:
			 *
			 *   listen("NPC::changedTile",someNPC,&C::someMethod);
			 *
			 *   with someNPC a reference to the actual stored NPC
			 *   and someMethod(NPC& npc, std::pair<Tile,Tile> tilePair)
			 *   tilePair.first will be tileBefore
			 *   tilePair.second will be tileAfter
			 *
			 * To stop listening later:
			 *
			 *   unlisten("NPC::changedTile",someNPC);
			 */
			npc->trigger("NPC::changedTile",
					std::pair<Tile, Tile>(tileBefore, tileAfter));
			tileBefore.removeNPC(npc);
			tileAfter.addNPC(npc);
		}
		// Juste un test pour le EventManager (activer debug dans HScenario.cc pour le voir)
		if (npc->hasArrived() or !wasArrived) {
			(*npc).trigger("NPC::arrived");
			DBG << "suppression d'un NPC";
			this->supprimerNPC(npc);

		}
		if (DEBUG) {
			std::list<NPC*> neighbours =
					(npc)->getPosition().isInTile(*map).getNPCsInRadius(*map,
							2);
			while (!neighbours.empty()) {
				NPC* tempNPC = neighbours.front();
				neighbours.pop_front();
				if (tempNPC->getUuid() != (npc)->getUuid()) {
					const std::string id1 = boost::lexical_cast<std::string>(
							npc->getUuid());
					const std::string id2 = boost::lexical_cast<std::string>(
							tempNPC->getUuid());
					printf("NPC %s: neighbour %s\n", id1.c_str(), id2.c_str());
				}
			}
		}
	}

	for (Player& player : players)
		DBG << "GlobalState : Position of player " << player.getID() << " : "
				<< player.getPosition();
	server->update(dt);
	return;
}

Server* GlobalState::getServer(void) {
	return server;
}

