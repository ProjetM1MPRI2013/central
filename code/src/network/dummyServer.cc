#include "debug.h"
#include "dummyServer.h"
#include "dummyClient.h"
#include "gameUpdate.h"

/*
 * @author mheinric
 */

using namespace std ;

DummyServer::DummyServer() : clients(), players(), received_messages(),
  updateGen(NULL){
}

DummyServer::~DummyServer(){
    for(DummyClient* cli : clients)
    {
        cli->isShutDown = true ;
    }
    MapType::iterator it2  ;
    for(it2 = received_messages.begin();it2 != received_messages.end(); it2++)
      {
        for(AbstractMessage* p : it2->second)
          delete p ;
      }
    received_messages.clear();
}

void DummyServer::addClient(DummyClient *cli){
    clients.insert(cli) ;
}

void DummyServer::removeClient(DummyClient * cli){
  clients.erase(cli);
}

void DummyServer::addMessage(AbstractMessage *msg, std::string msgType, DummyClient *cli){
  if(msgType.compare(NetEvent::getMsgType()) == 0)
    {
      //Handle netEvents
      NetEvent * event = (NetEvent *) msg ;
      if(handle_netEvent(*event, cli))
        {
          delete msg ;
          return ;
        }
    }
  lock.lock() ;
  received_messages[msgType].push_back(msg) ;
  lock.unlock() ;
}


vector<AbstractMessage *> DummyServer::receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &)){
    MapType::iterator p =  received_messages.find(msgType) ;
    if(p != received_messages.end())
      {
        lock.lock() ;
        vector<AbstractMessage *>temp(p->second) ;
        received_messages.erase(p);
        lock.unlock() ;
        return temp ;
      }
    else
      return vector<AbstractMessage* >() ;
}

void DummyServer::send_message(AbstractMessage& msg, bool, std::string msgType, int player ) {
  if(player == -1)
    {
      //Broadcast message
      for(DummyClient * client : clients)
          client->addMessage(msg.copy(),msgType);
    }
  else
    {
      //Send to specified client
      std::map<int, DummyClient*>::iterator it = players.find(player) ;
      if(it == players.end())
        {
          LOG(warning) << "Server : Could not find the specified player : " << player;
          return ;
        }
      it->second->addMessage(msg.copy(), msgType);
    }
}

bool DummyServer::handle_netEvent(NetEvent& event, DummyClient *client){
  switch(event.getType())
    {
    case NetEvent::CLI_LOST : {
        break ;
      }
    case NetEvent::CLI_RESP : {
        break ;
      }
    case NetEvent::CLI_TRY : {
        //Cannot be received by the server
        assert(false) ;
        break ;
      }
    case NetEvent::MSG_LOST : {
        break ;
      }
    case NetEvent::NOT_SET : {
        //Do not send NetEvent with type not set.
        assert(false) ;
        break ;
      }
    case NetEvent::PLAYER_JOIN : {
        int player = event.getData() ;
        players[player] = client;
        break ;
      }
    case NetEvent::PLAYER_QUIT : {
        int player = event.getData() ;
        players.erase(player);
        break ;
      }
    case NetEvent::RECEIVE_ERR : {
        break ;
      }
    case NetEvent::SEND_ERR : {
        break ;
      }
    case NetEvent::SERV_LOST : {
        break ;
      }
    case NetEvent::SERV_RESP : {
        break ;
      }
    case NetEvent::SERV_TRY : {
        client->addMessage(new NetEvent(NetEvent::SERV_RESP), NetEvent::getMsgType());
        break ;
      }
    case NetEvent::ACK : {
        // No Ack for the dummy implementation
        assert(false) ;
        break ;
      }
    }
  return false ;
}

vector<int> DummyServer::getConnectedPlayers(){
  vector<int> v ;
  for(std::pair<int, DummyClient *> p : players)
    {
      v.push_back(p.first);
    }
  return v ;
}

bool DummyServer::isConnected(int player){
  return players.find(player) != players.end() ;
}

void DummyServer::setSimulation(GlobalState *simu) {
  if(updateGen != NULL)
    LOG(error) << "SERVER: Simulation already set" ;
  updateGen = new UpdateGenerator(simu, this) ;
}

void DummyServer::update(sf::Time dt) {
  if(updateGen == NULL)
    LOG(warning) << "SERVER: Cannot update, no Simulation attached" ;
  else
    updateGen->update(dt);
}




