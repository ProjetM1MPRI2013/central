#include <assert.h>
#include "dummyClient.h"
#include "netEvent.h"

DummyClient::DummyClient(DummyServer* server) : received_messages(){
  this->server = server ;
  this->server->addClient(*this);
  this->addMessage(new NetEvent(NetEvent::SERV_RESP),NetEvent::getMsgType());
}

DummyClient::~DummyClient(){
  MapType::iterator it ;
  for(it = received_messages.begin(); it != received_messages.end(); it++)
    {
      delete it->second ;
    }
  received_messages.clear();
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
  if(received_messages[msgType] == NULL)
      received_messages[msgType] = new std::vector<AbstractMessage *>() ;

  received_messages[msgType]->push_back(msg) ;
  lock.unlock() ;
}

void DummyClient::send_message(AbstractMessage& msg, bool , std::string msgType ) {
  server->addMessage(msg.copy(), msgType, this) ;
}

std::vector<AbstractMessage *>& DummyClient::receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) {
  lock.lock() ;
  MapType::iterator p = received_messages.find(msgType) ;
  if(p != received_messages.end())
    {
      std::vector<AbstractMessage *> *temp = p->second ;
      received_messages.erase(p);
      lock.unlock() ;
      return *temp ;
    }
  else
    {
      lock.unlock() ;
      return *(new std::vector<AbstractMessage *>()) ;
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
    }

  return false ;
}

