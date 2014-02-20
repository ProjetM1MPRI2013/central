/**
  *@author Denys Kanunikov
  */

#include <SFML/Graphics.hpp>
#include "main.h"
#include "test.h"
#include "HScenario.h"
#include "globalState.h"
#include "test_globalstate.h"
#include "geography.h"
#include "tilemap.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "abstractMessage.h"
#include <boost/uuid/uuid_io.hpp>

#define DEBUG false
#include "debug.h"

using namespace boost::archive ;

namespace UUID_test
{

void createNPCs(int number, GlobalState& glob, GraphicContextIso& graContIso,
    Geography& geo, std::default_random_engine npcGen) {
  std::uniform_real_distribution<float>
      npcDistX(0.01, geo.getMapWidth() - 0.01);
  std::uniform_real_distribution<float> npcDistY(0.01, geo.getMapHeight()
      - 0.01);
  for (int i = 0; i < number; i++) {
    Position start = Position(npcDistX(npcGen), npcDistY(npcGen));
    Position target = Position(npcDistX(npcGen), npcDistY(npcGen));
    while (start.isInTile(geo).getSpeed() == 0) {
      start = Position(npcDistX(npcGen), npcDistY(npcGen));
    }
    while (target.isInTile(geo).getSpeed() == 0 || target.isInTile(geo).equals(
        start.isInTile(geo))) {
      target = Position(npcDistX(npcGen), npcDistY(npcGen));
    }

    NPC *msg = new NPC(1, 10, 10, start, textures::get(i% 2));

    msg->setTarget(target,*(glob.getMap()));
    msg->getPosition().isInTile(*(glob.getMap())).addNPC(msg);

    glob.addNPC(start, target, 1, textures::get(i % 2), msg->getUuid());
    LOG(info) << "Server : " << "Broadcast 1 message of type NPC:\n" << (*msg);
    glob.getServer()->broadcastMessage<NPC>(*msg);
    sleep(1);
   }
}
}


namespace test {
  int globalstate() {
    std::string seed = "424242";
    auto nbPlayers = 1;
    Geography geo = Generation1(seed);
    LOG(debug) << "address of geo " << &geo;
    GlobalState glob = GlobalState(&geo,nbPlayers, 1);
    LOG(debug) << "address of map in GlobalState " << glob.getMap();
    ServerInfo serv_info ;
    Server * ser = Network::createServer(serv_info) ;
    glob.setServer(ser);
    LOG(debug) << "address of server " << ser;
    LOG(debug) << "address of server in GlobalState " << glob.getServer();

    std::vector<TestA*> mes;
    GraphicContextIso graContIso = GraphicContextIso(&geo, &glob);
    std::default_random_engine npcGen(42);
    sleep(2);
    UUID_test::createNPCs(10, glob, graContIso, (*glob.getMap()), npcGen);

    while (true){
        mes = glob.getServer()->receiveMessages<TestA>();
        LOG(info) << "TEST : " << "Received " << mes.size() << " messages "  ;
        for(TestA* p : mes)
            LOG(info) << p->data << "; " ;
        sleep(1);
    }
    LOG(info) << "Global State testing done.";
    delete ser ;

    return 0;
  }
}

