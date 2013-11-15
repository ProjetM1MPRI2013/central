#include "dummyServer.h"
#include "dummyClient.h"

using namespace std ;

DummyServer::DummyServer() : clients(){
    events = new vector<Event> ;
}

DummyServer::~DummyServer(){
    delete events ;
    vector<DummyClient *>::iterator it ;
    for(it = clients.begin(); it != clients.end() ; it++)
    {
        delete *it ;
    }
}

void DummyServer::addClient(DummyClient &cli){
    clients.push_back(&cli) ;
}

void DummyServer::addEvent(Event &event){
    events->push_back(event) ;
}

void DummyServer::sendUpdate(GameState &game_state){
    vector<DummyClient*>::iterator cli ;
    for(cli = clients.begin(); cli != clients.end() ; cli++)
    {
        //Create gameUpdate from gameState
        //Missing code here
        GameUpdate game_update ;
        (*cli)->addUpdate(game_update) ;
    }
}

vector<Event>& DummyServer::receiveEvents(){
    vector<Event> *p = events ;
    events = new vector<Event>() ;
    return *p ;
}

vector<NetEvent>& DummyServer::receiveNetEvents(){
    return *(new vector<NetEvent>()) ;
}
