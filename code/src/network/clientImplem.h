#ifndef CLIENT_IMPLEM_H
#define CLIENT_IMPLEM_H

#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/asio.hpp>

#include "client.h"
#include "netEvent.h"
#include "comunicatorImplem.h"



/**
 * @brief The ClientImplem class
 *  Class implementing the Client interface. It is used for communication
 *  between the server and the Client.
 *  This class relies on UDP protocol for communication. A custom protocol is
 *  added on top of UDP to ensure packet delivery when it is necessary (basically,
 *  when the client sends an event to the server).
 *
 *  This class uses asynchronous send/recieve, and stores eventually the results.
 *  This is necessary to ACK messages, and to resend thoses who have not been recieved.
 *  Because it is asynchronous, it requires a thread running background operations
 *  (send, recieve, resend, ack...).
 *
 *  The messages that will be sent must have this form :
 *  - a header containing the type of the message (8 bits), the message number (used to identify messages, 4 bits)
 *  and wether it should be acked or not (1 bit).
 *  - data : provided by the toString method of the message
 *
 *  In pariticular, the size of the message sent is not sent. This is possible because
 *  we use a datagram oriented protocol. For this protocol to work, it is important that
 *  messages can be sent in only one datagram (and it should be checked that it is
 *  effectively the case).
 */

class ClientImplem : public Client, public ComunicatorImplem {


public :
    /*
    Methods inherited from the Client interface
    See client.h for details
   */
    ClientImplem(ClientInfo& c_info) ;
    virtual~ClientImplem() ;

private :
    //Prevent copy
    ClientImplem(ClientImplem&) = delete ;
    ClientImplem operator =(const ClientImplem&) = delete ;

protected :
    virtual void send_message(AbstractMessage& msg, bool reliable, std::string msgType ) ;
      virtual std::vector<AbstractMessage *> receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) ;

protected :

    /**
     * @brief server_endpoint
     * Address of the server
     */
    endpoint server_endpoint ;


   /**
    * @brief on_sent
    * Function called after a send operation has been made.
    * This function is responsible to call further operations to ensure
    * we received a ACK
    */
    void on_sent(const std::vector<std::string*> &buffer, const error_code &error, int) ;

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
    void check_ack(std::vector<std::string*>& msg, int nb_times, deadline_timer *t, const boost::system::error_code &err) ;

    /**
     * @brief wait_receive : adds a 'wait for a new message task to the poll'
     */
    void inline wait_receive() ;

} ;

#endif
