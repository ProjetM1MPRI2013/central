#include "NewMov.h"
#include <iostream>


void printNewMov(NewMov nm){
  switch (nm){
  case P_RIGHT:
    std::cout << "P_RIGHT";
    break;
  case P_LEFT:
    std::cout << "P_LEFT";
    break;
  case P_UP:
   std::cout << "P_UP";
    break;
  case P_DOWN:
   std::cout << "P_DOWN";
    break;
  case R_RIGHT:
   std::cout << "R_RIGHT";
    break;
  case R_LEFT:
   std::cout << "R_LEFT";
    break;
  case R_UP:
   std::cout << "R_UP";
    break;
  case R_DOWN:
   std::cout << "R_DOWN";
    break;
  default:
    std::cout << "Unknown NewMov";
    break;
  }
}

NewMovNetwork::NewMovNetwork(NewMov m, int pid){
  this->movement = m;
  this->playerID = pid;
}

//AbstractMessage function implementations
std::string NewMovNetwork::getMsgType(){
  std::string s = "C_MOVEME";
  return s;
}

std::string NewMovNetwork::toString(){
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
