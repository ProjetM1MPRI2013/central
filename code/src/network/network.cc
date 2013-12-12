#include "network.h"
#include "clientImplem.h"
#include "serverImplem.h"
#include "dummyClient.h"
#include "dummyServer.h"

Server& Network::createServer(ServerInfo s_info){
    return *(new ServerImplem(s_info)) ;
}

Client& Network::createClient(ClientInfo c_info){
    return *(new ClientImplem(c_info)) ;
}

DummyServer* Network::createDummyServer(){
    return (new DummyServer()) ;
}

DummyClient* Network::createDummyClient(Server* server){
        return (new DummyClient((DummyServer*) server)) ;
}


UpdateGenerator *Network::createUpdater(Simulation *globalState, Server *server){
  return new UpdateGenerator(globalState, server) ;
}

LocalStateUpdater* createUpdater(LocalState* localState, Client* client) {
  return new LocalStateUpdater(localState, client) ;
}
