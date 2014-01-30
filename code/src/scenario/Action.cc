#define DEBUG true
#include "debug.h"

#include "Action.h"

#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>

#include "ActionsPC.h"
#include "ActionsTerro.h"

BOOST_CLASS_EXPORT(Action)

Action::Action(std::string n, Simulation* s) {
  name = n;
  simulation = s;
  this->playerID = this->simulation->getPlayer()->getID ();
}

Action::Action(const Action& a){
  this->name = a.name;
  this->simulation = a.simulation;
  this->playerID = a.playerID;
}

bool Action::isActionPossible(){
  std::cerr << "isActionPossible called but not implemented for the Action type :" << name << "\n";
  return 0;
}

void Action::doAction(){
  std::cerr << "doAction called but not implemented for the Action type :" << name << "\n";
  return;
}

void Action::addPendingActions(HostSimulation* hs){
  std::cerr << "addPendingActions called but not implemented for the Action type :" << name << "\n";
  return;
}


Action::Action() : name(""), date(0), delay(0), simulation(NULL), playerID(0){}


//AbstractMessage function implementations
std::string Action::getMsgType(){
  return "Sce:C_ACTION";
}

std::string Action::toString(){
  std::stringstream ss ;
  boost::archive::text_oarchive ar(ss) ;
  ar << *this ;
  return ss.str();
}

AbstractMessage* Action::fromString(std::string& msg){
  Action a ;
  std::stringstream ss(msg) ;
  boost::archive::text_iarchive ar(ss) ;
  DBG << ss.str() ;
  ar >> a ;
  DBG << ss.str() ;
  if(a.name.compare("AddCam") == 0)
    {
      //AddCam* event = new AddCam() ;
      //DBG << ss.str() ;
    }
  return NULL ;
}

AbstractMessage* Action::copy(){
  return ((AbstractMessage*)new Action(*this));
}
