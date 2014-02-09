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
#define DEBUG false
#include "debug.h"

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
