/**
 */
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

#include "abstractMessage.h"

#ifndef ACTIONBOOST_H
#define ACTIONBOOST_H


BOOST_CLASS_EXPORT(A_Attack);
BOOST_CLASS_EXPORT(A_Reload);
BOOST_CLASS_EXPORT(A_Plant);
BOOST_CLASS_EXPORT(A_Drop);

#endif
