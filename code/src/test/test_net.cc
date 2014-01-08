#include <iostream>
#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <thread>
#include <chrono>

#include "test_net.h"
#include "network/network.h"
#include "network/netEvent.h"
#include "simulation/localState.h"
#include "network/dummyClient.h"
#include "network/dummyServer.h"



using namespace std;
using namespace boost::archive ;

class TestA : public AbstractMessage {

public :

  TestA(int t){
    data = t ;
  }

  static std::string getMsgType() { return "TypeA000" ;}

  virtual std::string & toString() {
    stringstream ss ;
    text_oarchive ar(ss) ;
    ar << *this ;
    return *(new string(ss.str())) ;
  }

  static AbstractMessage * fromString(std::string& msg){
    stringstream ss(msg) ;
    text_iarchive ar(ss) ;
    NetEvent* e = new NetEvent() ;
    ar >> *e ;
    return e ;
  }

  virtual AbstractMessage* copy() {
    return new TestA(*this) ;
  }

  int data ;

private :
  //Serialization

  friend class boost::serialization::access ;

  template <class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & data ;
  }

};

class TestB : public AbstractMessage {

public :

  TestB(int t){
    data = t ;
  }

  static std::string getMsgType() { return "TypeB000" ;}

  virtual std::string & toString() {
    stringstream ss ;
    text_oarchive ar(ss) ;
    ar << *this ;
    return *(new string(ss.str())) ;
  }

  static AbstractMessage * fromString(std::string& msg){
    stringstream ss(msg) ;
    text_iarchive ar(ss) ;
    NetEvent* e = new NetEvent() ;
    ar >> *e ;
    return e ;
  }

  virtual AbstractMessage* copy() {
    return new TestB(*this) ;
  }

  int data ;

private :
  //Serialization

  friend class boost::serialization::access ;

  template <class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & data ;
  }
};

int test_cli_ser(Server* ser, Client* cli){

  //Test from client to server.

  TestA m_1(1) ;

  cout << "Sending 1 message of type A from Client to Server with data  :" << endl  ;
  cout << m_1.data << endl ;
  cli->sendMessage<TestA>(m_1) ;
  this_thread::sleep_for(chrono::milliseconds(400)) ;

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
  this_thread::sleep_for(chrono::milliseconds(400)) ;

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
    cout << ".....FAIL" << endl ;

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
  this_thread::sleep_for(chrono::milliseconds(400)) ;
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
  this_thread::sleep_for(chrono::milliseconds(400)) ;
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
  this_thread::sleep_for(chrono::milliseconds(400)) ;

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
  this_thread::sleep_for(chrono::milliseconds(400)) ;

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

int test_net_dummy(){
  cout << "Dummy Test ......... BEGIN" << endl ;
  Server *ser = Network::createDummyServer() ;
  Client *cli = Network::createDummyClient(ser) ;
  int i = test_cli_ser(ser,cli) ;
  cout << "Dummy Test ........ FINISHED" << endl ;
  return i ;
}

int test_net_real(){
  cout << "Real Test ......... BEGIN" << endl ;
  ClientInfo cli_info ;
  ServerInfo serv_info ;
  Server * ser = Network::createServer(serv_info) ;
  Client * cli = Network::createClient(cli_info) ;
  int i = test_cli_ser(ser,cli) ;
  cout << "Real Test ........ FINISHED" << endl ;
  return i ;
}
