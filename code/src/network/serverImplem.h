#ifndef SERVER_IMPLEM_H 
#define SERVER_IMPLEM_H

#include <boost/asio.hpp>
#include <set>

#include "server.h"
#include "comunicatorImplem.h"
#include "netEvent.h"

/**
 * @brief The ServerImplem class
 * Network implementation of the Server interface.
 * It uses a custom protocol on top of udp to send messages.
 * @see ClientImplem
 */
class ServerImplem : virtual public Server, public ComunicatorImplem {
public :
    /*
    Methods inherited from the Server interface
    See client.h for details
   */
    ServerImplem(ServerInfo& c_info) ;
    virtual ~ServerImplem() ;

    virtual std::vector<int> getConnectedPlayers() ;

    virtual bool isConnected(int player) ;

private :
    //Prevent copy
    ServerImplem(ServerImplem&) = delete ;
    ServerImplem operator =(const ServerImplem&) = delete ;

protected :
    virtual void send_message(AbstractMessage& msg, bool reliable, std::string msgType, int player) ;
      virtual std::vector<AbstractMessage *> receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) ;

    /**
     * @brief server_endpoint
     * Contains all the addresses of the Clients connected to this server.
     */
    std::set<endpoint> client_endpoints ;


    /**
     * @brief registered_players : all the players registered to this server.
     * A given player is registered when the server receives a PLAYER_JOIN message
     * with a field data containing the id of the player. The endpoint that sent the message is
     * then associated with this player.
     */
    std::map<int, endpoint> registered_players;

    /**
     * @brief sender_endpoint : buffer to store the endpoint
     * of the sender of received message
     */
    endpoint sender_endpoint ;

    /**
    * @brief on_sent
    * Function called after a send operation has been made.
    * This function is responsible to call further operations to ensure
    * we recieved a ACK
    */
    void on_sent(std::vector<std::string*> &buffer, endpoint cli_endpoint, const error_code &error, int) ;

    /**
     * @brief on_recieve
     * Called when a datagram is recieved. Responsible to treat
     * the content, and eventually store it
     */
    void on_receive(const boost::system::error_code &error, int size) ;

    /**
     * @brief check_ack
     * function called to check wether an ACK was recieved for a
     * given message. If not, it will resend the message, and wait again
     * for an ACK.
     * @param msg : the message that was sent
     * @param nb_times : the number of times the message has already been resent
     * @param t : the timer associated to the resend.
     * @param err : the error code associated with the wait event this function will be called by.
     *
     * The function takes ownership of the message and the timer (is responsible for
     * destroying them when they ar no longer needed).
     */
    void check_ack(std::vector<std::string*>& msg, endpoint cli_endpoint ,
                   int nb_times, deadline_timer *t, const boost::system::error_code &err) ;

    /**
     * @brief wait_receive : adds a 'wait for a new message task to the poll'
     */
    void inline wait_receive() ;

} ;

#endif 
