#ifndef DUMMYCLIENT_H
#define DUMMYCLIENT_H

#include "client.h"
#include "dummyServer.h"
#include "dummytypes.h"

using namespace std ;


class DummyClient : public Client{
public:
    DummyClient(DummyServer& server);
    ~DummyClient() ;

    void addUpdate(GameUpdate& gu) ;

private :
    vector<GameUpdate>* recieved_updates;
    DummyServer* server ;

    /*
     * Methods inherited from the server interface
     */

public :

    virtual void sendEvent(Event& event) ;

    virtual vector<GameUpdate>& recieveUpdates() ;

    virtual vector<NetEvent>& recieveNetEvents() ;
};

#endif // DUMMYCLIENT_H
