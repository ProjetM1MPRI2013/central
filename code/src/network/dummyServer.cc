#include "dummyServer.h"
#include "dummyClient.h"
#include "gameUpdate.h"

using namespace std ;

DummyServer::DummyServer() : clients(), received_messages(){
}

DummyServer::~DummyServer(){
    list<DummyClient *>::iterator it ;
    for(it = clients.begin(); it != clients.end() ; it++)
    {
        delete *it ;
    }
    MapType::iterator it2  ;
    for(it2 = received_messages.begin();it2 != received_messages.end(); it2++)
      {
        delete it2->second ;
      }
    received_messages.clear();
}

void DummyServer::addClient(DummyClient &cli){
    clients.push_back(&cli) ;
}

void DummyServer::addMessage(AbstractMessage &msg, std::string msgType, DummyClient *cli){
  if(msgType.compare(NetEvent::getMsgType()) == 0)
    {
      //Handle netEvents
      NetEvent & event = (NetEvent &) msg ;
      if(handle_netEvent(event, *cli))
        return ;
    }

  MapType::iterator p = received_messages.find(msgType) ;
  if(p == received_messages.end())
    {
      p = received_messages.insert(MapType::value_type(msgType, new vector<AbstractMessage *>()) ).first ;
    }
  lock.lock() ;
  p->second->push_back(&msg) ;
  lock.unlock() ;
}

void DummyServer::sendUpdate(GameState &game_state){
    list<DummyClient*>::iterator cli ;
    for(cli = clients.begin(); cli != clients.end() ; cli++)
    {
        //Create gameUpdate from gameState
        //Missing code here
        GameUpdate game_update ;
        (*cli)->addMessage(game_update, GameUpdate::getMsgType()) ;
    }
}

vector<AbstractMessage *>& DummyServer::receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &)){
    MapType::iterator p =  received_messages.find(msgType) ;
    if(p != received_messages.end())
      {
        lock.lock() ;
        vector<AbstractMessage *>* temp = p->second ;
        received_messages.erase(p);
        lock.unlock() ;
        return *temp ;
      }
    else
      return *(new vector<AbstractMessage* >()) ;
}

void DummyServer::broadcast_message(AbstractMessage& msg, bool, std::string msgType ) {
  for(DummyClient * client : clients)
    {
      client->addMessage(*msg.copy(),msgType);
    }
}

bool DummyServer::handle_netEvent(NetEvent& event, DummyClient &client){
  //TODO : some stuff
  return false ;
}




