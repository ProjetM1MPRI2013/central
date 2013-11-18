#ifndef CLIENT_IMPLEM_H
#define CLIENT_IMPLEM_H

#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/asio.hpp>
#include "client.h"




/**
 * @brief The ClientImplem class
 *  Class implementing the Client interface. It is used for communication
 *  between the server and the Client.
 *  This class relies on UDP protocol for communication. A custo protocol is
 *  added on top of UDP to ensure packet delivery when it is necessary (basically,
 *  when the client sends an event to the server.
 *
 *  This class uses asynchronous send/recieve, and stores eventually the results.
 *  This is necessary to ACK messages, and to resend thoses who have not been recieved.
 *  Because it is asynchronous, it requires a thread running background operations
 *  (send, recieve, resend, ack...).
 *
 *  The messages that will be sent must have this form :
 *  -> 1 bit  : message type
 *  -> 4 bits : message ident
 *  -> rest data
 *
 *  In pariticular, the size of the message sent is not sent. This is possible because
 *  we use a datagram oriented protocol. For this protocol to work, it is important that
 *  messages can be sent in only one datagram (and it should be checked that it is
 *  effectively the case).
 *
 *  The type of the message is distributed as follow :
 *  -> 0 : connection messages, reserved for Network implementation
 *  -> 1 : Aknoledgment messages (in this case, the ident represents the message that is
 *         beeing acked.
 *  -> 2 : Event messages (Safe delivery through ACK)
 *  -> 3 : GameUpdate messages (Server->Client), usafe delivery
 *  -> ... : other types of messages can be added later.
 */



using namespace boost::asio ;
using namespace std;

class ClientImplem : public Client {

public :
    /*
    Methods inherited from the Client interface
    See client.h for details
   */
    ClientImplem(ClientInfo c_info) ;
    ~ClientImplem() ;
    //virtual void sendEvent(Event& event) ;
    //virtual std::vector<GameUpdate>& recieveUpdates() ;
    //virtual std::vector<NetEvent>& recieveNetEvents() ;

protected :
    virtual void send_message(AbstractMessage& msg, bool reliable, std::string msgType ) {
      //TODO missing implementation
    }
    virtual std::vector<AbstractMessage *>& receive_messages(std::string msgType, AbstractMessage* (*f) (std::string *) ) {
      //TODO missing implementation
    }

public :
    /**
     * @brief BUFF_SIZE
     * size of the buffer used for recieve operations.
     * messages should not have a greater size, this may cause problems
     */
    const static int BUFF_SIZE = 1000;

    /**
     * @brief TIME_TO_WAIT
     * time to wait (in ms) before resending the message.
     */
    const static int TIME_TO_WAIT = 100 ;

    /**
     * @brief NB_TRY
     * number of times the client should try to send the message.
     * if no ack has been recieved after that, the server is believed
     * to be unreacheable, and the client goes into an error state
     * (error gestion to be precised)
     */
    const static int NB_TRY = 10 ;

protected :

    /**
     * @brief server_endpoint
     * Address of the server
     */
    ip::udp::endpoint server_endpoint ;

    /**
     * Socket used to recieve and send informations to the server
     */
    ip::udp::socket *sock ;

    /**
     * Element used to dispach events on the Client.
     * Sending and recieving informations through the socket is
     * made asynchronously. This service is used to dispach the
     * tasks to a thread.
     * This will be necessary to deal with packet loss when sending
     * events to the server.
     */
    io_service *service ;

    /**
     * set used to store the messages sent but not yet acked.
     * when an ack is recieved, the corresponding number is
     * removed from this set, to prevent resending the data.
     */
    set<int> ack_set ;

    /**
     * @brief recieved_updates
     * vector used to store the recieved GameUpdates.
     * This is the vector returned when calling to recieveUpdates()
     */
    //vector<GameUpdate>* recieved_updates ;

    /**
     * @brief buff
     * Used as a buffer to temporarily store the results of
     * recieve operations.
     */
    string *buff ;

    /**
    * @brief on_sent
    * Function called after a send operation has been made.
    * This function is responsible to call further operations to ensure
    * we recieved a ACK
    */
    void on_sent(string &msg, const boost::system::error_code &error, int size) ;

    /**
     * @brief on_recieve
     * Called when a datagram is recieved. Responsible to treat
     * the content, and eventually store it
     */
    void on_recieve(const boost::system::error_code &error, int size) ;

    /**
     * @brief init_connexion
     * exchange basic informations with the server (game version, players names ...)
     * start the io thread.
     */
    void init_connexion() ;

    /**
     * @brief shutdown
     * properly shuts down the connexion with the server.
     */
    void shutdown() ;

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
    void check_ack(string &msg, int nb_times, deadline_timer *t, const boost::system::error_code &err) ;

    int get_msg_type(string &msg) ;

    int get_msg_nb(string &msg) ;



} ;

#endif
