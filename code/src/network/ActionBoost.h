
/*********************************************************
** @author: Remy (generated code)**
*********************************************************/
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/utility.hpp>
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_serialize.hpp"
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
#include "abstractMessage.h"
#ifndef ACTIONBOOST_H
#define ACTIONBOOST_H
BOOST_CLASS_EXPORT(A_Attack);
BOOST_CLASS_EXPORT(A_Reload);
BOOST_CLASS_EXPORT(A_Plant);
BOOST_CLASS_EXPORT(A_Drop);
BOOST_CLASS_EXPORT(C_Stuff);
BOOST_CLASS_EXPORT(C_Weapon);
BOOST_CLASS_EXPORT(C_Gun);
BOOST_CLASS_EXPORT(C_Mitraillette);
BOOST_CLASS_EXPORT(C_UltraM);
BOOST_CLASS_EXPORT(C_Knife);
BOOST_CLASS_EXPORT(C_Ammunition);
BOOST_CLASS_EXPORT(C_Bomb);
#endif
