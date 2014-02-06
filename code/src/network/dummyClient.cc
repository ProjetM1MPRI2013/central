#include <assert.h>

#include "debug.h"
#include "dummyClient.h"
#include "netEvent.h"
#include "simulation/localState.h"

/*
 * @author mheinric
 */

DummyClient::DummyClient(DummyServer* server) : received_messages(),
  locStateUpdater(NULL){
  this->server = server ;
  this->server->addClient(this);
  this->addMessage(new NetEvent(NetEvent::SERV_RESP),NetEvent::getMsgType());
}

DummyClient::~DummyClient(){
  if(!isShutDown)
    server->removeClient(this);
  MapType::iterator it ;
  lock.lock() ;
  for(it = received_messages.begin(); it != received_messages.end(); it++)
    {
      for(AbstractMessage* p : it->second)
        delete p ;
    }
  received_messages.clear();
  lock.unlock() ;
}

void DummyClient::addMessage(AbstractMessage *msg, std::string msgType){

  if(msgType.compare(NetEvent::getMsgType()) == 0){
      NetEvent* event = (NetEvent *) msg ;
      if(handle_netEvent(*event))
        {
          delete msg ;
          return ;
        }
    }
  lock.lock() ;
  received_messages[msgType].push_back(msg) ;
  lock.unlock() ;
}

void DummyClient::send_message(AbstractMessage& msg, bool , std::string msgType ) {
  if(!isShutDown)
    server->addMessage(msg.copy(), msgType, this) ;
  else
    LOG(warning) << "DummyClient : Trying to send message, but server is shut down" ;
}

std::vector<AbstractMessage *> DummyClient::receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) {
  lock.lock() ;
  MapType::iterator p = received_messages.find(msgType) ;
  if(p != received_messages.end())
    {
      std::vector<AbstractMessage *> temp(p->second) ;
      received_messages.erase(p);
      lock.unlock() ;
      return temp ;
    }
  else
    {
      lock.unlock() ;
      return std::vector<AbstractMessage *>() ;
    }
}

bool DummyClient::handle_netEvent(const NetEvent &event){
  switch(event.getType())
    {
    case NetEvent::CLI_LOST : {
        break ;
      }
    case NetEvent::CLI_RESP : {
        break ;
      }
    case NetEvent::CLI_TRY : {
        server->addMessage(new NetEvent(NetEvent::CLI_RESP), NetEvent::getMsgType(), this);
        return true ;
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
        break ;
      }
    case NetEvent::PLAYER_QUIT : {
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
        //Case not possible, only the client can send this message
        assert(false) ;
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


void DummyClient::setLocalState(LocalState *simu) {
  if(locStateUpdater != NULL)
    LOG(error) << "CLIENT: LocalState already set" ;
  locStateUpdater = new LocalStateUpdater(simu, this) ;
  NetEvent coevent(NetEvent::PLAYER_JOIN) ;
  coevent.setData(simu->getPlayer()->getID());
  sendMessage<NetEvent>(coevent) ;
}

void DummyClient::update(sf::Time dt) {
  if(locStateUpdater == NULL)
    LOG(warning) << "CLIENT: Cannot update, no Local State attached" ;
  else
    locStateUpdater->update(dt);
}

