#include "NewMov.h"


NewMovNetwork::NewMovNetwork(NewMov m, int pid){
  this->movement = m;
  this->playerID = pid;
}

//AbstractMessage function implementations
std::string NewMovNetwork::getMsgType(){
  std::string s = "C_MOVEME";
  return s;
}

std::string & NewMovNetwork::toString(){
  std::string s = "TODO";
  return s;
}

AbstractMessage* NewMovNetwork::fromString(std::string& msg){
  //TODO
  return ((AbstractMessage*) new NewMovNetwork(P_RIGHT, 42));
}

AbstractMessage* NewMovNetwork::copy(){
  return ((AbstractMessage*) new NewMovNetwork(this->movement, this->playerID));
}
