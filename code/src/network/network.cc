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

Server& Network::createDummyServer(){
    return *(new DummyServer()) ;
}

Client& Network::createDummyClient(Server& server){
        return *(new DummyClient((DummyServer&) server)) ;
}
