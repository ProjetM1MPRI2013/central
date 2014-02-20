/**
  *@author Denys Kanunikov
  */

#include <SFML/Graphics.hpp>
#include "main.h"
#include "test.h"
#include "HScenario.h"
#include "localState.h"
#include "test_localstate.h"
#include "geography.h"
#include "tilemap.h"
#define DEBUG false
#include "debug.h"
#include <boost/uuid/uuid_io.hpp>

namespace test {
  int localstate() {
    std::string seed = "424242";
    auto nbPlayers = 1;
    Geography geo = Generation1(seed);
    LOG(debug) << "address of geo " << &geo;
    LocalState loc = LocalState(&geo,nbPlayers, 1);
    LOG(debug) << "address of map in LocalState " << loc.getMap();
    ClientInfo client_info;
    Client *client = Network::createClient(client_info);
    LOG(info) << "Client created at "<< client;
    loc.setClient(client);
    LOG(info) << "Client attached to LocalState at "<< loc.getClient();
    GraphicContextIso graContIso = GraphicContextIso(&geo, &loc);

    TestA msg(0);
    std::vector<NPC*> mes;
    while (true){
        msg.data ++;
        LOG(info) << "Client : " << "Send a message <TestA> with data:"
                     << msg.data;
        loc.getClient()->sendMessage<TestA>(msg) ;
        sleep(1);
        mes = loc.getClient()->receiveMessages<NPC>();
        LOG(info) << "Client : " << "Received <NPC>" << mes.size() << " messages "  ;
        for(NPC* p : mes){
            loc.addNPC(p->position, p->getTarget(), p->getSpeed(),
                      textures::get(1), p->getUuid());
            LOG(info) << "NPC :\n" << (*p)<< "; " ;

        }
        sleep(1);
    }

    LOG(info) << "Local State testing done.";

    return 0;
  }
}


