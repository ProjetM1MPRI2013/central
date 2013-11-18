#include "dummyClient.h"

DummyClient::DummyClient(DummyServer& server) : received_messages(){
  this->server = &server ;
  this->server->addClient(*this);
}

DummyClient::~DummyClient(){
  MapType::iterator it ;
  for(it = received_messages.begin(); it != received_messages.end(); it++)
    {
      delete it->second ;
    }
  received_messages.clear();
}

void DummyClient::addMessage(AbstractMessage &msg, std::string msgType){
  if(received_messages[msgType] == NULL)
      received_messages[msgType] = new std::vector<AbstractMessage *>() ;

  received_messages[msgType]->push_back(&msg) ;
}

void DummyClient::send_message(AbstractMessage& msg, bool , std::string msgType ) {
  server->addMessage(msg, msgType) ;
}

std::vector<AbstractMessage *>& DummyClient::receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) {
  MapType::iterator p = received_messages.find(msgType) ;
  if(p != received_messages.end())
    {
      std::vector<AbstractMessage *> *temp = p->second ;
      received_messages.erase(p);
      return *temp ;
    }
  else
    return *(new std::vector<AbstractMessage *>()) ;
}


