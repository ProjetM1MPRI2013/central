#ifndef CLIENT_IMPLEM_H
#define CLIENT_IMPLEM_H

#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/asio.hpp>
#include "client.h"
#include "netEvent.h"




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

class ClientImplem : public Client {

  /*
   * Type shortcuts
   */
  typedef boost::asio::ip::udp::endpoint endpoint ;
  typedef boost::asio::ip::udp::socket socket ;
  typedef boost::asio::io_service io_service ;
  typedef boost::system::error_code error_code ;
  typedef boost::asio::deadline_timer deadline_timer ;

public :
    /*
    Methods inherited from the Client interface
    See client.h for details
   */
    ClientImplem(ClientInfo c_info) ;
    ~ClientImplem() ;

protected :
    virtual void send_message(AbstractMessage& msg, bool reliable, std::string msgType ) {
      //TODO missing implementation
    }
    virtual std::vector<AbstractMessage *>& receive_messages(std::string msgType, AbstractMessage* (*f) (std::string &) ) {
      //TODO missing implementation
    }

public :
    /**
     * @brief HEADER_SIZE : the size of the header used to transfer messages.
     * 8 bits for message type.
     * 4 bits for message number
     * 1 bit for ack
     */
    const static int HEADER_SIZE = 13 ;

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
     * to be unreacheable a NetEvent with type SERV_LOST is generated
     */
    const static int NB_TRY = 10 ;

protected :

    /**
     * @brief server_endpoint
     * Address of the server
     */
    endpoint server_endpoint ;

    /**
     * Socket used to recieve and send informations to the server
     */
    socket *sock ;

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
    std::set<int> ack_set ;

    typedef std::map<std::string,std::vector<std::string> > mapType ;
    /**
     * @brief recieved_updates
     * vector used to store the recieved GameUpdates.
     * This is the vector returned when calling to recieveUpdates()
     */
    mapType received_messages ;

    /**
     * @brief header_buff
     * Used as a buffer to temporarily store the header of received messages
     */
    std::string *header_buff ;

    /**
     * @brief buff
     * Used as a buffer to temporarily store the results of
     * recieve operations.
     */
    std::string *buff ;

    /**
    * @brief on_sent
    * Function called after a send operation has been made.
    * This function is responsible to call further operations to ensure
    * we recieved a ACK
    */
    void on_sent(std::vector<std::string*> &buffer, const error_code &error, int) ;

    /**
     * @brief on_recieve
     * Called when a datagram is recieved. Responsible to treat
     * the content, and eventually store it
     */
    void on_recieve(const boost::system::error_code &error, int size) ;

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
    void check_ack(std::vector<std::string*>& msg, int nb_times, deadline_timer *t, const boost::system::error_code &err) ;

    /**
     * @brief get_msg_type : gives the type of the message header passed as argument
     * @return : the type of the message
     */
    std::string get_msg_type(std::string &header) ;

    /**
     * @brief get_msg_nb : gives the id of the message corresponding to the
     * header passed in argument
     * @return the id of the message
     */
    int get_msg_id(std::string & header) ;

    /**
     * @brief generate_message : generates a NetEvent message on this
     * side. (used to inform of possible failures).
     * The caller keep ownership of the message which can be destroyed immediatetly
     * after it ha been sent.
     * @param event : the NetEvent to add to the pending events on this side of the
     * communication.
     */
    void generate_message(NetEvent& event) ;

    /**
     * @brief ack_message : whether or not this message awaits an ack.
     * @param header : the header of the message
     * @return : true if this message must be acked (reliable message)
     */
    bool ack_message(std::string& header) ;

} ;

#endif
