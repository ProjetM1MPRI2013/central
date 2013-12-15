#include <iostream>

#include "test_net.h"
#include "network/network.h"
#include "network/netEvent.h"
#include "simulation/localState.h"
#include "network/dummyClient.h"
#include "network/dummyServer.h"


using namespace std;

class TestA : public AbstractMessage {

public :

  TestA(int t){
    data = t ;
  }

  static std::string getMsgType() { return "TypeA" ;}

  virtual std::string & toString() { return *(new string()) ;}

  static AbstractMessage * fromString(std::string& msg){ return NULL ;}

  virtual AbstractMessage* copy() {
    return new TestA(*this) ;
  }

  int data ;
};

class TestB : public AbstractMessage {

public :

  TestB(int t){
    data = t ;
  }

  static std::string getMsgType() { return "TypeB" ;}

  virtual std::string & toString() { return *(new string()) ;}

  static AbstractMessage * fromString(std::string& msg){ return NULL ;}

  virtual AbstractMessage* copy() {
    return new TestB(*this) ;
  }

  int data ;
};

int test_net(){
  Server *ser = Network::createDummyServer() ;
  Client *cli = Network::createDummyClient(ser) ;

  //Test from client to server.

  TestA m_1(1) ;

  cout << "Sending 1 message of type A from Client to Server with data  :" << endl  ;
  cout << m_1.data << endl ;
  cli->sendMessage<TestA>(m_1) ;
  vector<TestA*> va= ser->receiveMessages<TestA>() ;
  cout << "Received " << va.size() << " messages of type A with data : " << endl ;
  for(TestA* p :va)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;
  vector<TestB*> vb = ser->receiveMessages<TestB>() ;
  cout << "Received " << vb.size() << " messages of type B with data : " << endl ;
  for(TestB* p :vb)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;


  if(va.size() == 1 && vb.size() == 0 && va[0]->data == m_1.data)
    cout << ".....OK" << endl ;
  else
    cout << ".....FAIL" << endl ;



  //Test from server to client.

  cout << "Sending 1 message of type A from Server to Client with data  :" << endl  ;
  cout << m_1.data << endl ;
  ser->broadcastMessage<TestA>(m_1) ;
  va= cli->receiveMessages<TestA>() ;
  cout << "Received " << va.size() << " messages of type A with data : " << endl ;
  for(TestA* p :va)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;
  vb = cli->receiveMessages<TestB>() ;
  cout << "Received " << vb.size() << " messages of type B with data : " << endl ;
  for(TestB* p :vb)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;


  if(va.size() == 1 && vb.size() == 0 && va[0]->data == m_1.data)
    cout << ".....OK" << endl ;
  else
    cout << ".....FAIL" ;

  //Test with several messages Client -> Server

  cout << "Sending 3 messages of type A from Client to Server, with data : " << endl ;
  int i ;
  for(i =0 ; i < 3 ; i++)
    {
      TestA temp_m(i) ;
      cli->sendMessage<TestA>(temp_m) ;
      cout << temp_m.data << "; " ;
    }
  cout << endl ;
  va= ser->receiveMessages<TestA>() ;
  cout << "Received " << va.size() << " messages of type A with data : " << endl ;
  for(TestA* p :va)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;
  vb = ser->receiveMessages<TestB>() ;
  cout << "Received " << vb.size() << " messages of type B with data : " << endl ;
  for(TestB* p :vb)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;

  if(va.size() == 3 && vb.size() == 0 && va[0]->data == 0 && va[1]->data == 1 && va[2]->data ==2 )
    cout << ".....OK" << endl ;
  else
    cout << ".....FAIL" << endl ;


  //Test with several messages Server -> Client

  cout << "Sending 3 messages of type A from Server to Client, with data : " << endl ;
  for(i =0 ; i < 3 ; i++)
    {
      TestA temp_m(i) ;
      ser->broadcastMessage<TestA>(temp_m) ;
      cout << temp_m.data << "; " ;
    }
  cout << endl ;
  va= cli->receiveMessages<TestA>() ;
  cout << "Received " << va.size() << " messages of type A with data : " << endl ;
  for(TestA* p :va)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;
  vb = cli->receiveMessages<TestB>() ;
  cout << "Received " << vb.size() << " messages of type B with data : " << endl ;
  for(TestB* p :vb)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;

  if(va.size() == 3 && vb.size() == 0 && va[0]->data == 0 && va[1]->data == 1 && va[2]->data ==2 )
    cout << ".....OK" << endl ;
  else
    cout << ".....FAIL" << endl ;


  //Test with several types at the same time Client -> Server

  TestA me_A(10) ;
  TestB me_B(20) ;
  cout << "Sending messages from Client to Server :" << endl;
  cout << "1 messages of type A with data : " <<  me_A.data << endl ;
  cout << "1 messages of type B with data : " <<  me_B.data << endl ;
  cli->sendMessage<TestA>(me_A) ;
  cli->sendMessage<TestB>(me_B) ;

  va= ser->receiveMessages<TestA>() ;
  cout << "Received " << va.size() << " messages of type A with data : " << endl ;
  for(TestA* p :va)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;
  vb = ser->receiveMessages<TestB>() ;
  cout << "Received " << vb.size() << " messages of type B with data : " << endl ;
  for(TestB* p :vb)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;

  if(va.size() == 1 && vb.size() == 1 && va[0]->data == me_A.data && vb[0]->data == me_B.data)
    cout << ".....OK" << endl;
  else
    cout << ".....FAIL" << endl;


  //Test with several types at the same time Server -> Client


  cout << "Sending messages from Server to Client :" << endl;
  cout << "1 messages of type A with data : " <<  me_A.data << endl ;
  cout << "1 messages of type B with data : " <<  me_B.data << endl ;
  ser->broadcastMessage<TestA>(me_A) ;
  ser->broadcastMessage<TestB>(me_B) ;

  va= cli->receiveMessages<TestA>() ;
  cout << "Received " << va.size() << " messages of type A with data : " << endl ;
  for(TestA* p :va)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;
  vb = cli->receiveMessages<TestB>() ;
  cout << "Received " << vb.size() << " messages of type B with data : " << endl ;
  for(TestB* p :vb)
    {
      cout << p->data << "; " ;
    }
  cout << endl ;

  if(va.size() == 1 && vb.size() == 1 && va[0]->data == me_A.data && vb[0]->data == me_B.data)
    cout << ".....OK" << endl;
  else
    cout << ".....FAIL" << endl;




  return 0 ;
}
