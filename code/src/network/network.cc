#include "network.h"

#include <assert.h>

#include "clientImplem.h"
#include "serverImplem.h"
#include "dummyClient.h"
#include "dummyServer.h"
#include "simulation/localState.h"
#include "simulation/simulation.h"



Server* Network::createServer(ServerInfo s_info){
  return new ServerImplem(s_info) ;
}

Client* Network::createClient(ClientInfo c_info){
  return new ClientImplem(c_info) ;
}

Server* Network::createDummyServer(){
  return new DummyServer() ;
}

Client* Network::createDummyClient(Server* server){
  DummyServer * ser = dynamic_cast<DummyServer*>(server) ;
  //Accepts only DummyServers as argument
  assert(ser != NULL) ;
  return new DummyClient(ser) ;
}


UpdateGenerator *Network::createUpdater(Simulation *globalState, Server *server){
  return new UpdateGenerator(globalState, server) ;
}

LocalStateUpdater* createUpdater(LocalState* localState, Client* client) {
  return new LocalStateUpdater(localState, client) ;
}
