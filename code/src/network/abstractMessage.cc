#include <sstream>
#include "boost/uuid/uuid_serialize.hpp"
#include "boost/uuid/uuid_io.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "ActionBoost.h"
#include "abstractMessage.h"
#include "netEvent.h"
#include "test/test_net.h"
#include "gameUpdate.h"
#include "scenario/Action.h"
#include "scenario/ActionsPC.h"
#include "scenario/ActionsTerro.h"
#include "scenario/NewMov.h"
#include "scenario/ScenarioAction.h"
#include "scenario/ScenarioActionList.h"
#include "interfaceinit/chat_event.h"
#include "simulation/npc.h"
/*
 * @author mheinric
 */

//Registers the classes used for serialization
BOOST_CLASS_EXPORT(AbstractMessage)
BOOST_CLASS_EXPORT(NetEvent)
BOOST_CLASS_EXPORT(test::TestA)
BOOST_CLASS_EXPORT(test::TestB)
BOOST_CLASS_EXPORT(GameUpdate)
BOOST_CLASS_EXPORT(Action)
BOOST_CLASS_EXPORT(AddCop)
BOOST_CLASS_EXPORT(AddCam)
BOOST_CLASS_EXPORT(NewMouseMovNetwork)
BOOST_CLASS_EXPORT(NewMovNetwork)
BOOST_CLASS_EXPORT(ScenarioAction)
BOOST_CLASS_EXPORT(ChangeDirection)
BOOST_CLASS_EXPORT(ChangeDestination)
BOOST_CLASS_EXPORT(AddCams)
BOOST_CLASS_EXPORT(AddCops)
BOOST_CLASS_EXPORT(ChatEvent)
BOOST_CLASS_EXPORT(NPC)

#include "debug.h"

using namespace std ;
using namespace boost::archive ;

AbstractMessage* AbstractMessage::fromString(const std::string &msg){
  try{
  stringstream ss(msg) ;
  AbstractMessage* message = NULL;
  {
    text_iarchive ar(ss) ;
    ar >> message ;
  }
  DBG << "Deserialize from : " << msg ;
  return message ;
  } catch(...) {
    LOG(error) << "Could not deserialize message  : " << msg ;
    return NULL ;
  }
}

string AbstractMessage::toString() {
  stringstream ss ;
  {
    text_oarchive ar(ss) ;
    AbstractMessage * this2 = this;
    ar << this2 ;
  }
  DBG << "Serialize to : " << ss.str() ;
  return ss.str() ;
}
