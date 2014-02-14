#ifndef COMUNICATORIMPLEM_H
#define COMUNICATORIMPLEM_H

#include <boost/asio.hpp>
#include <set>
#include <thread>
#include <mutex>
#include <queue>
#include <boost/function.hpp>

#include "netEvent.h"

/**
 * @brief The ComunicatorImplem class
 * Base class for the Network implementation of the client and the server.
 *
 * This class contains utility functions that are used on both sides.
 * @author mheinric
 */
class ComunicatorImplem
{
public:

  ComunicatorImplem();
  virtual ~ComunicatorImplem();

  /**
   * @brief HEADER_SIZE : the size of the header used to transfer messages.
   * 8 bits for message type.
   * 4 bits for message number
   * 1 bit for ack
   */
  const static unsigned int HEADER_SIZE = 13 ;

  /**
   * @brief BUFF_SIZE
   * size of the buffer used for recieve operations.
   * messages should not have a greater size, this may cause problems
   */
  const static unsigned int BUFF_SIZE = 1000;

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

  /*
   * Type shortcuts
   */
  typedef boost::asio::ip::udp::endpoint endpoint ;
  typedef boost::asio::ip::udp::socket socket ;
  typedef boost::asio::io_service io_service ;
  typedef boost::system::error_code error_code ;
  typedef boost::asio::deadline_timer deadline_timer ;

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
   * @brief recieved_messages
   * vector used to store the recieved GameUpdates.
   * This is the vector returned when calling to recieveUpdates()
   */
  mapType received_messages ;

  std::mutex received_messages_mutex ;

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
   * @brief sent_ack
   * Contains the ack that were sent to the server.
   * used to prevent duplicates of messages.
   * Elements in this set remain in it only for a period of time
   * (basically a few seconds after the message is received).
   */
  std::set<int> sent_ack ;

  /**
   * @brief lock : used to prevent concurrent writings on the socket
   */
  std::mutex lock ;

  /**
   * @brief pending_writes : stores pending write operations.
   * Used to prevent concurrent write.
   */
  std::queue< boost::function<void(void)> > pending_writes ;

  /**
   * @brief can_write : true if there is no write operation beeing performed
   */
  bool can_write ;

  /**
   * @brief last_sent : number attributed to the last sent message
   */
  int last_sent ;

  /**
   * @brief work : used to keep io_service busy. when destroyed, will allow run() method to return.
   */
  boost::asio::io_service::work * work ;

  /**
   * @brief net_thread : the thread that is running the Client/Server operations (ie : send, receive...)
   */
  std::thread* net_thread ;

  /**
   * @brief nb_tasks : number of tasks that are currently running on the io_service
   * This counter is used to assert that there is no pending task when the io_service is
   * shut down, and thus that all used memory was freed.
   * Only the async_write and async_wait are counted.
   * async_read handlers do not need to free any memory (and we don't know when the handler will be called)
   */
  int nb_tasks = 0 ;

  /**
   * @brief nb_tasks_mutex : used to modify concurrently the number of running tasks
   */
  std::mutex nb_tasks_mutex ;

  /**
   * @brief shut_down true if this instance is beeing detroyed (used to notify the running tasks)
   */
  bool is_shutdown = false ;


  /**
   * @brief shutdown
   * properly shuts down the connexion with the server.
   */
  void shutdown() ;

  /**
   * @brief get_msg_type : gives the type of the message header passed as argument
   * @return : the type of the message
   */
  std::string get_msg_type(const std::string &header) ;

  /**
   * @brief get_msg_nb : gives the id of the message corresponding to the
   * header passed in argument
   * @return the id of the message
   */
  int get_msg_id(const std::string & header) ;

  /**
   * @brief generate_message : generates a NetEvent message on this
   * side. (used to inform of possible failures).
   * The caller keep ownership of the message which can be destroyed immediatetly
   * after it ha been sent.
   * @param event : the NetEvent to add to the pending events on this side of the
   * communication.
   */
  void generate_message(NetEvent event) ;

  /**
   * @brief ack_message : whether or not this message awaits an ack.
   * @param header : the header of the message
   * @return : true if this message must be acked (reliable message)
   */
  bool ack_message(const std::string& header) ;

  /**
   * @brief create_header : creates a header for a message with the given parameters
   * @param reliable : wether a ACK is awaited or not.
   * @param type : the type of message sent.
   * @param id : id of the message
   * @return : a HEADER_SIZE lenght string representing the header of the message.
   */
  std::string* create_header(bool reliable, std::string type, int id) ;

  /**
   * @brief write_buff : allow write operation in a concurrent way
   * @param buffers : the buffers to send
   * @param : the endpoint to send the message to, default to NULL, meaning the socket is already connected
   * @param hanlder : the handler that will be called when the write op is finished.
   */
  void write_buff(std::vector<boost::asio::const_buffer> buffers,
                  boost::function<void(const error_code&, int)> handler,
                  endpoint* rec_endpoint = NULL) ;

  /**
   * @brief increase_tasks : increases the counter of pending tasks
   */
  void increase_tasks() ;

  /**
   * @brief decrease_tasks : decreses the counter of pending tasks
   */
  void decrease_tasks() ;

};

#endif // COMUNICATORIMPLEM_H
