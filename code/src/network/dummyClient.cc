#include "dummyClient.h"

DummyClient::DummyClient(DummyServer& server){
    recieved_updates = new vector<GameUpdate>() ;
    this->server = &server ;
}

DummyClient::~DummyClient(){
    delete recieved_updates ;
}

void DummyClient::addUpdate(GameUpdate &gu){
    recieved_updates->push_back(gu);
}

void DummyClient::sendEvent(Event &event){
    server->addEvent(event);
}

vector<GameUpdate>& DummyClient::recieveUpdates(){
    vector<GameUpdate>* p = recieved_updates ;
    recieved_updates = new vector<GameUpdate>() ;
    return *p ;
}

vector<NetEvent>& DummyClient::recieveNetEvents(){
    return *(new vector<NetEvent>()) ;
}
