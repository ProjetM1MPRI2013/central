#include "ScenarioAction.h"

#include <sstream>

ScenarioAction::ScenarioAction (std::string n, Simulation* s){
  simulation = s;
  name = n;
  date = 0; //TODO
}

ScenarioAction::ScenarioAction(const ScenarioAction& a){
  this->date = a.date;
  this->name = a.name;
  this->simulation = a.simulation;
}


void ScenarioAction::run(){
  return;
}

//AbstractMessage function implementations
std::string ScenarioAction::getMsgType(){
  std::string s ("H_SACTIO");
  return s;
}

std::string ScenarioAction::toString(){
  std::stringstream ss ;
  boost::archive::text_oarchive ar(ss) ;
  ar << *this ;
  return ss.str() ;
}

ScenarioAction::ScenarioAction() : date(0), name(){}

AbstractMessage* ScenarioAction::fromString(std::string& msg){
  std::stringstream ss(msg) ;
  boost::archive::text_iarchive ar(ss) ;
  ScenarioAction* e = new ScenarioAction() ;
  ar >> *e ;
  return e ;
}

AbstractMessage* ScenarioAction::copy(){
  return ((AbstractMessage*)new ScenarioAction(*this));
}
