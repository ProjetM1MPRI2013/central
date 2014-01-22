#ifndef DUMMYCLIENT_H
#define DUMMYCLIENT_H

#include <map>
#include <mutex>
#include "client.h"
#include "dummyServer.h"
#include "netEvent.h"
#include "localStateUpdater.h"

/**
 * @brief The DummyClient class
 * Class used for debug. Provides an implementation of the
 * Client interface. Will just copy the events, and not use
 * the network, nor carry out any serialization
 */

class DummyClient : public Client{

  friend DummyServer::~DummyServer() ;

public:
  /**
   * @brief DummyClient
   * Creates a new Client, connected to the server.
   * All events sent will be copied to the server
   * The server will copy any update to the client
   * @param server : the server the Client will connect to
   */
  DummyClient(DummyServer* server);

  /**
   * @brief addMessage : adds a pending message to this client
   * @param msg : the message to add
   * @param msgType : the type of message to add
   * The Client gains ownership of the message in argument.
   * The message must not be deleted after the call.
   */
  void addMessage(AbstractMessage *msg, std::string msgType) ;

protected :
  /**
   * protected destructor : the client will be
   * destroyed either when the server is destroyed,
   * or by call to shutdown (not implemented for now).
   */
  virtual ~DummyClient() ;

  typedef std::map<std::string, std::vector<AbstractMessage*>* > MapType ;

  /**
   * @brief recieved_updates
   * Stores the updates recieved from now.
   * To each message type, associates a vector composed of
   * the received messages of this type.
   */
  MapType received_messages;

  /**
   * @brief lock : used to prevent concurrent acces to the container containing all the messages.
   */
  std::mutex lock ;
  /**
   * @brief server
   * The server this client is connected to.
   */
  DummyServer* server ;

  /**
   * @brief handle_netEvent : handles NetEvent when they are received.
   * @param event
   * @return true if the event must not be passed to the user. false otherwise
   */

  LocalStateUpdater* locStateUpdater;

  virtual bool handle_netEvent(const NetEvent& event) ;

    /*
     * Methods inherited from the Client interface
     */
  virtual void send_message(AbstractMessage &msg, bool reliable, std::string msgType ) ;

  virtual std::vector<AbstractMessage *> receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) ;

  virtual void setLocalState(LocalState *simu);

  virtual void update(sf::Time dt);


};

#endif // DUMMYCLIENT_H
