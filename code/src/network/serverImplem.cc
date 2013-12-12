#include"serverImplem.h"

#include <assert.h>


ServerImplem::ServerImplem(ServerInfo s_info) {
  assert(false) ;
    service = new io_service() ;
    sock = new ip::udp::socket(*service) ;
}

/*void ServerImplem::sendUpdate(GameState &game_state){
  return ; 
} */
/*
vector<Event>& ServerImplem::receiveEvents(){
  return *(new std::vector<Event>()) ;
}

vector<NetEvent>& ServerImplem::receiveNetEvents(){
    return *(new vector<NetEvent>()) ;
}
*/
