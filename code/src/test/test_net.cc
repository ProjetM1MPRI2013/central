#include <iostream>

#include "test_net.h"
#include "network/network.h"
#include "network/netEvent.h"
#include "simulation/localState.h"
#include "network/dummyClient.h"
#include "network/dummyServer.h"


using namespace std;

int test_net(){
  Server *ser = Network::createDummyServer() ;
  Client *cli = Network::createDummyClient(ser) ;
  NetEvent e ;
  e.setType(NetEvent::PLAYER_JOIN);
  int player_id = 0 ;
  e.setData(&player_id);
  cli->sendMessage(e) ;

  vector<NetEvent *> v = ser->receiveMessages<NetEvent>() ;
  if(v.size() != 1)
    {
      cout << "wrong size : " << v.size() << endl ;
      return 1 ;
    }
  if(v[0]->getType() != NetEvent::PLAYER_JOIN)
    {
      cout << "wrong type : " << (int) v[0]->getType() << endl ;
    }
  cout << "server : OK" << endl ;

  ser->broadcastMessage(e) ;
  vector<NetEvent *> v2 = cli->receiveMessages<NetEvent>() ;
  if(v2.size() != 2)
    {
      cout << "wrong size 2: " << v2.size() << endl ;
      return 1 ;
    }
  if(v2[1]->getType() != NetEvent::PLAYER_JOIN)
    {
      cout << "wrong type 2: " << (int) v2[0]->getType() << endl ;
      return 1 ;
    }

  cout << "basic verification : DONE" << endl ;
  cout << "testing with the Local and global state" << endl ;

  Player locPlayer(player_id, 0,0) ;
  Player globPlayer(player_id, 0,0) ;
  LocalState locState(locPlayer,"");
  Simulation globState("", std::vector<Player *>(1,&globPlayer)) ;

  LocalStateUpdater locUpdater(&locState, cli) ;
  UpdateGenerator globUpdater(&globState, ser) ;

  int step ;
  for(step = 0 ; step < 2 ; step ++)
    {
      cout << "Global : Player moving UP" << endl ;

      Player* p = globState.getPlayerByID(player_id);
      p->setDirection(UP);

      globState.run(sf::seconds(1.0f));

      cout << "Global : Position of the player is now : " << p->getPosition()->getX() << ", "
           << p->getPosition()->getY() << endl ;

      cout << "Global : call update to broadcast updates" << endl ;

      globUpdater.update();

      cout << "Local : apply updates" << endl ;

      locUpdater.update();

      Player* lp = &locState.getOwnerLocalState() ;
      cout << "Local : Observed position of the local player : " << lp->getPosition()->getX() << ", "
           << lp->getPosition()->getY() << endl ;

      cout << "Fin du step " << step << endl ;
    }

  return 0 ;
}
