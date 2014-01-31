#include <iostream>
#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <thread>
#include <chrono>

#include "debug.h"
#include "test_net.h"
#include "network/network.h"
#include "network/netEvent.h"
#include "network/dummyClient.h"
#include "network/dummyServer.h"

BOOST_CLASS_EXPORT(test::TestC)
BOOST_CLASS_EXPORT(test::TestD)


namespace test {


using namespace std;
using namespace boost::archive ;

int net_serialization(){
  LOG(info) << "" ;
  LOG(info) << "Simple serialization" ;
  TestC* testcMsg = new TestC() ;
  testcMsg->data = 100 ;
  TestC * testcp = NULL ;
  stringstream ssc ;
  {
    text_oarchive oarch(ssc) ;
    oarch << testcMsg ;
  }
  text_iarchive iarch(ssc) ;
  iarch >> testcp ;
  assert(testcp != NULL) ;
  if(testcp->data != testcMsg->data)
    LOG(info) << "TEST : .........FAIL" ;
  else
    LOG(info) << "TEST : ...........OK" ;


  LOG(info) << "Simple serialization with inheritance" ;
  TestD* derived = new TestD() ;
  derived->data = 10 ;
  derived->data2 = 20 ;
  TestC* base = derived ;
  TestC* result = NULL ;
  stringstream ssc2 ;
  text_oarchive oarch2(ssc2) ;
  oarch2 << base ;
  text_iarchive iarch2(ssc2) ;
  iarch2 >> result ;
  assert(result != NULL) ;
  if(result->data != derived->data || ((TestD *) result)->data2 != derived->data2 )
    {
      LOG(info) << "data : " << result->data << " data2 : " << ((TestD *) result)->data2 ;
      LOG(info) << "TEST : .........FAIL" ;
    }
  else
    LOG(info) << "TEST : ...........OK" ;

  TestA msg(1) ;
  msg.data2 = 10 ;
  string s = msg.toString() ;
  TestA* msg2 = (TestA*) TestA::fromString(s) ;
  LOG(info) << "TEST : class TestA before serialisation : data = " << msg.data << ", after : data = " << msg2->data ;
  LOG(info) << msg.data2 << "-------" << msg2->data2 ;
  if(msg2->data != msg.data)
    LOG(info) << "TEST : .........FAIL" ;
  else
    LOG(info) << "TEST : ...........OK" ;
  delete msg2 ;

  TestB msg3(20) ;
  s = msg3.toString() ;
  TestB* msg4 = (TestB*) TestB::fromString(s) ;
  LOG(info) << "TEST : class TestB before serialisation : data = " << msg3.data << ", after : data = " << msg4->data ;
  if(msg4->data != msg3.data)
    LOG(info) << "TEST : .........FAIL" ;
  else
    LOG(info) << "TEST : ...........OK" ;
  delete msg4 ;
/*
  AddCam event ;
  event.date = 100 ;
  string s2 = event.toString() ;
  Action* rec = (Action*) Action::fromString(s2) ;

  if(event.date != rec ->date)
    LOG(info) << "TEST : .........FAIL" ;
  else
    LOG(info) << "TEST : ...........OK" ;
*/
  return 0 ;
}



int test_cli_ser(Server* ser, Client* cli){

  //Test from client to server.

  TestA m_1(1) ;

  LOG(info) << "TEST : " << "Sending 1 message of type A from Client to Server with data  :" ;
  LOG(info) << m_1.data ;
  cli->sendMessage<TestA>(m_1) ;
  this_thread::sleep_for(chrono::milliseconds(40)) ;

  vector<TestA*> va= ser->receiveMessages<TestA>() ;
  LOG(info) << "TEST : " << "Received " << va.size() << " messages of type A with data : " ;
  for(TestA* p :va)
    {
      LOG(info) << p->data << "; " ;
    }
  vector<TestB*> vb = ser->receiveMessages<TestB>() ;
  LOG(info) << "TEST : " << "Received " << vb.size() << " messages of type B with data : "  ;
  for(TestB* p :vb)
    {
      LOG(info) << p->data << "; " ;
    }


  if(va.size() == 1 && vb.size() == 0 && va[0]->data == m_1.data)
    LOG(info) << "TEST : " << ".....OK"  ;
  else
    LOG(info) << "TEST : " << ".....FAIL"  ;



  //Test from server to client.

  LOG(info) << "TEST : " << "Sending 1 message of type A from Server to Client with data  :"   ;
  LOG(info) << m_1.data  ;
  ser->broadcastMessage<TestA>(m_1) ;
  this_thread::sleep_for(chrono::milliseconds(40)) ;

  va= cli->receiveMessages<TestA>() ;
  LOG(info) << "TEST : " << "Received " << va.size() << " messages of type A with data : "  ;
  for(TestA* p :va)
    {
      LOG(info) << p->data << "; " ;
    }
  vb = cli->receiveMessages<TestB>() ;
  LOG(info) << "TEST : " << "Received " << vb.size() << " messages of type B with data : "  ;
  for(TestB* p :vb)
    {
      LOG(info) << p->data << "; " ;
    }


  if(va.size() == 1 && vb.size() == 0 && va[0]->data == m_1.data)
    LOG(info) << "TEST : " << ".....OK"  ;
  else
    LOG(info) << "TEST : " << ".....FAIL"  ;

  //Test with several messages Client -> Server

  LOG(info) << "TEST : " << "Sending 3 messages of type A from Client to Server, with data : "  ;
  int i ;
  for(i =0 ; i < 3 ; i++)
    {
      TestA temp_m(i) ;
      cli->sendMessage<TestA>(temp_m) ;
      LOG(info) << temp_m.data << "; " ;
    }
  this_thread::sleep_for(chrono::milliseconds(40)) ;
  va= ser->receiveMessages<TestA>() ;
  LOG(info) << "TEST : " << "Received " << va.size() << " messages of type A with data : "  ;
  for(TestA* p :va)
    {
      LOG(info) << p->data << "; " ;
    }
  vb = ser->receiveMessages<TestB>() ;
  LOG(info) << "TEST : " << "Received " << vb.size() << " messages of type B with data : "  ;
  for(TestB* p :vb)
    {
      LOG(info) << p->data << "; " ;
    }

  if(va.size() == 3 && vb.size() == 0 && va[0]->data == 0 && va[1]->data == 1 && va[2]->data ==2 )
    LOG(info) << "TEST : " << ".....OK"  ;
  else
    LOG(info) << "TEST : " << ".....FAIL"  ;


  //Test with several messages Server -> Client

  LOG(info) << "TEST : " << "Sending 10 messages of type A from Server to Client, with data : "  ;
  for(i =0 ; i < 3 ; i++)
    {
      TestA temp_m(i) ;
      ser->broadcastMessage<TestA>(temp_m) ;
      LOG(info) << temp_m.data << "; " ;
    }
  this_thread::sleep_for(chrono::milliseconds(40)) ;
  va= cli->receiveMessages<TestA>() ;
  LOG(info) << "TEST : " << "Received " << va.size() << " messages of type A with data : "  ;
  for(TestA* p :va)
    {
      LOG(info) << p->data << "; " ;
    }
  vb = cli->receiveMessages<TestB>() ;
  LOG(info) << "TEST : " << "Received " << vb.size() << " messages of type B with data : "  ;
  for(TestB* p :vb)
    {
      LOG(info) << p->data << "; " ;
    }

  if(va.size() == 3 && vb.size() == 0 && va[0]->data == 0 && va[1]->data == 1 && va[2]->data ==2 )
    LOG(info) << "TEST : " << ".....OK"  ;
  else
    LOG(info) << "TEST : " << ".....FAIL"  ;


  //Test with several types at the same time Client -> Server

  TestA me_A(10) ;
  TestB me_B(20) ;
  LOG(info) << "TEST : " << "Sending messages from Client to Server :" ;
  LOG(info) << "TEST : " << "1 messages of type A with data : " <<  me_A.data  ;
  LOG(info) << "TEST : " << "1 messages of type B with data : " <<  me_B.data  ;
  cli->sendMessage<TestA>(me_A) ;
  cli->sendMessage<TestB>(me_B) ;
  this_thread::sleep_for(chrono::milliseconds(40)) ;

  va= ser->receiveMessages<TestA>() ;
  LOG(info) << "TEST : " << "Received " << va.size() << " messages of type A with data : "  ;
  for(TestA* p :va)
    {
      LOG(info) << p->data << "; " ;
    }
  vb = ser->receiveMessages<TestB>() ;
  LOG(info) << "TEST : " << "Received " << vb.size() << " messages of type B with data : "  ;
  for(TestB* p :vb)
    {
      LOG(info) << p->data << "; " ;
    }

  if(va.size() == 1 && vb.size() == 1 && va[0]->data == me_A.data && vb[0]->data == me_B.data)
    LOG(info) << "TEST : " << ".....OK" ;
  else
    LOG(info) << "TEST : " << ".....FAIL" ;


  //Test with several types at the same time Server -> Client


  LOG(info) << "TEST : " << "Sending messages from Server to Client :" ;
  LOG(info) << "TEST : " << "1 messages of type A with data : " <<  me_A.data  ;
  LOG(info) << "TEST : " << "1 messages of type B with data : " <<  me_B.data  ;
  ser->broadcastMessage<TestA>(me_A) ;
  ser->broadcastMessage<TestB>(me_B) ;
  this_thread::sleep_for(chrono::milliseconds(40)) ;

  va= cli->receiveMessages<TestA>() ;
  LOG(info) << "TEST : " << "Received " << va.size() << " messages of type A with data : "  ;
  for(TestA* p :va)
    {
      LOG(info) << p->data << "; " ;
    }
  vb = cli->receiveMessages<TestB>() ;
  LOG(info) << "TEST : " << "Received " << vb.size() << " messages of type B with data : "  ;
  for(TestB* p :vb)
    {
      LOG(info) << p->data << "; " ;
    }

  if(va.size() == 1 && vb.size() == 1 && va[0]->data == me_A.data && vb[0]->data == me_B.data)
    LOG(info) << "TEST : " << ".....OK" ;
  else
    LOG(info) << "TEST : " << ".....FAIL" ;

  return 0 ;
}

int net_dummy(){
  LOG(info) << "TEST : " << "Dummy Test ......... BEGIN"  ;
  Server *ser = Network::createDummyServer() ;
  Client *cli = Network::createDummyClient(ser) ;
  int i = test_cli_ser(ser,cli) ;
  LOG(info) << "TEST : " << "Dummy Test ........ FINISHED"  ;
  return i ;
}

int net_real(){
  LOG(info) << "TEST : " << "Real Test ......... BEGIN"  ;
  ClientInfo cli_info ;
  ServerInfo serv_info ;
  Server * ser = Network::createServer(serv_info) ;
  Client * cli = Network::createClient(cli_info) ;

  int i = test_cli_ser(ser,cli) ;
  LOG(info) << "TEST : " << "Real Test ........ FINISHED"  ;
  return i ;
}
}

