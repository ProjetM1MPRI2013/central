#ifndef DUMMYSERVER_H
#define DUMMYSERVER_H

#include "server.h"

class DummyClient ;

class DummyServer : public Server {
public:
    DummyServer();
    virtual ~DummyServer() ;
    void addClient(DummyClient& cli) ;
    void addEvent(Event& event) ;

private :
    std::vector<DummyClient*> clients ;
    std::vector<Event> *events ;

    /*
     *Methods inherited from Client
     */

public :

  virtual void sendUpdate(GameState &game_state) ;

  virtual std::vector<Event>& receiveEvents() ;

  virtual std::vector<NetEvent>& receiveNetEvents() ;

};

#endif // DUMMYSERVER_H
