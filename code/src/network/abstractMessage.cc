#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "abstractMessage.h"
#include "debug.h"
#include "netEvent.h"
#include "test/test_net.h"

BOOST_CLASS_EXPORT_IMPLEMENT(AbstractMessage)
BOOST_CLASS_EXPORT_IMPLEMENT(NetEvent)
BOOST_CLASS_EXPORT_IMPLEMENT(test::TestA)
BOOST_CLASS_EXPORT_IMPLEMENT(test::TestB)

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
    ar << this ;
  }
  DBG << "Serialize to : " << ss.str() ;
  return ss.str() ;
}
