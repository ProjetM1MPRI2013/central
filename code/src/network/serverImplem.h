#ifndef SERVER_IMPLEM_H 
#define SERVER_IMPLEM_H

#include <boost/asio.hpp>
#include "server.h"

using namespace boost::asio ;
using namespace std ;

/**
 * @brief The ServerImplem class
 * Network implementation of the Server interface.
 * (not implemented yet).
 */
class ServerImplem : public Server {
 protected :
  /*
    UDP socket used to communicate with clients
   */
  ip::udp::socket *sock ;

  /*
    io_service, used to dispach events to the thread(s)
   */
  io_service *service ;

  /*
    Container of the pending events recieved.
    With a mutex to prevent concurrent access.
   */
  //vector<Event> recieved_events ;
  //mutex stuff
  
  void on_recieve(/*some arg*/) ;

  virtual void send_message(AbstractMessage& msg, bool reliable, std::string msgType, int player = -1 ) {
    //TODO missing implementation
    return ;
  }
  virtual std::vector<AbstractMessage *>& receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) {
    //TODO missing implementation
    return *(new std::vector<AbstractMessage *>()) ;
  }

  virtual std::vector<int> getConnectedPlayers() {
    std::vector<int> v ;
    return v ;
  }

  virtual bool isConnected(int player){
    return false;
  }

 public :

  ServerImplem(ServerInfo s_info) ;  

  /*
   * Methods from Server Interface
   */
  //deprecated void sendUpdate(GameState& game_state) ;
  //vector<Event>& receiveEvents() ;
  //virtual vector<NetEvent>& receiveNetEvents() ;
} ;

#endif 
