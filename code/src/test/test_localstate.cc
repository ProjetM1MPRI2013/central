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

    TestA msg(0);
    while (true){
        msg.data ++;
        LOG(info) << "TEST : " << "Sending 1 message of type A from Client to Server with data  :" ;
        LOG(info) << msg.data ;
        loc.getClient()->sendMessage<TestA>(msg) ;
        sleep(2);
    }

    LOG(info) << "Local State testing done.";

    return 0;
  }
}
