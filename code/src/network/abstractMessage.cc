#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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

//Registers the classes used for serialization
BOOST_CLASS_EXPORT_IMPLEMENT(AbstractMessage)
BOOST_CLASS_EXPORT_IMPLEMENT(NetEvent)
BOOST_CLASS_EXPORT_IMPLEMENT(test::TestA)
BOOST_CLASS_EXPORT_IMPLEMENT(test::TestB)
BOOST_CLASS_EXPORT_IMPLEMENT(GameUpdate)
BOOST_CLASS_EXPORT_IMPLEMENT(Action)
BOOST_CLASS_EXPORT_IMPLEMENT(AddCop)
BOOST_CLASS_EXPORT_IMPLEMENT(AddCam)
BOOST_CLASS_EXPORT_IMPLEMENT(Drop)
BOOST_CLASS_EXPORT_IMPLEMENT(Attack)
BOOST_CLASS_EXPORT_IMPLEMENT(Plant)
BOOST_CLASS_EXPORT_IMPLEMENT(Reload)
BOOST_CLASS_EXPORT_IMPLEMENT(NewMovNetwork)
BOOST_CLASS_EXPORT_IMPLEMENT(ScenarioAction)
BOOST_CLASS_EXPORT_IMPLEMENT(ChangeDirection)
BOOST_CLASS_EXPORT_IMPLEMENT(KillNPC)
BOOST_CLASS_EXPORT_IMPLEMENT(Explosion)
BOOST_CLASS_EXPORT_IMPLEMENT(AddCams)
BOOST_CLASS_EXPORT_IMPLEMENT(AddCops)
BOOST_CLASS_EXPORT_IMPLEMENT(DropItem)
BOOST_CLASS_EXPORT_IMPLEMENT(ChatEvent)

#include "debug.h"

using namespace std ;
using namespace boost::archive ;

AbstractMessage* AbstractMessage::fromString(const std::string &msg){
  stringstream ss(msg) ;
  AbstractMessage* message = NULL;
  {
    text_iarchive ar(ss) ;
    ar >> message ;
  }
  DBG << "Deserialize from : " << msg ;
  return message ;
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
