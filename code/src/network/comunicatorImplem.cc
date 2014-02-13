#include <thread>
#include <chrono>

#include "comunicatorImplem.h"
#include "debug.h"

/*
 * @author mheinric
 */

using namespace std ;
using namespace boost::asio ;

ComunicatorImplem::ComunicatorImplem() : ack_set(), received_messages(), sent_ack(), lock(),
  pending_writes(), can_write(true), last_sent(0), nb_tasks_mutex(){
  //init fields
  service = new io_service() ;
  sock = new ip::udp::socket(*service) ;
  buff = new string(BUFF_SIZE, '\000') ;
  header_buff = new string(HEADER_SIZE, '\000') ;
  work = new io_service::work(*service) ;
  net_thread = new thread([this](){service->run() ;}) ;
}

ComunicatorImplem::~ComunicatorImplem(){
  shutdown() ;
  delete service ;
  delete sock ;
  delete buff ;
  delete header_buff ;
  delete net_thread ;
}

void ComunicatorImplem::shutdown(){
  DBG << "NET: Shutting down communication" ;
  delete work ;
  work = NULL ;
  is_shutdown = true ;
  while(nb_tasks != 0)
    {
      std::chrono::milliseconds dura( 300 );
      std::this_thread::sleep_for( dura );
    }
  service->stop();
  //not needed for a UDP socket
  //sock->shutdown(ip::udp::socket::shutdown_both);
  net_thread->join() ;
}

std::string ComunicatorImplem::get_msg_type(const string &header) {
  assert(header.size() == HEADER_SIZE) ;
  return header.substr(0, 8) ;
}

int ComunicatorImplem::get_msg_id(const string &header) {
  string id_s = header.substr(8,4) ;
  int res = 0 ;
  for(int i = 0 ; i < 4 ; i++)
    {
      res = 256*res + ((int) id_s.at(i)) ;
    }
  return res ;
}


void ComunicatorImplem::generate_message(NetEvent event) {
  //TODO change
  string msg = event.toString() ;
  received_messages[NetEvent::getMsgType()].push_back(msg) ;
}

bool ComunicatorImplem::ack_message(const string &header) {
  assert(header.size() == HEADER_SIZE) ;
  return (header[HEADER_SIZE -1] != '\00') ;
}

std::string* ComunicatorImplem::create_header(bool reliable, std::string type, int id) {
  assert(type.size() == 8) ;

  //asynchronous send necessite buffers to be saved on the heap
  string * header = new string(HEADER_SIZE, '\00') ;
  if(reliable)
    header->at(HEADER_SIZE -1) = '\001' ;
  int i ;
  for(i = 0 ; i < 8; i++)
    {
      header->at(i) = type[i] ;
    }
  header->at(11) = (char) id % 256 ;
  header->at(10) = (char) (id/256) % 256 ;
  header->at(9) = (char) (id/256/256) % 256 ;
  header->at(8) = (char) (id/256/256/256) % 256 ;

  return header ;
}

void ComunicatorImplem::write_buff(vector<const_buffer> buffers,
                                   boost::function<void(const error_code&, int)> handler,
                                   endpoint* rec_endpoint) {
  auto sync_handler = [this, handler](const error_code& error, int i)->void{
      decrease_tasks();
      handler(error, i) ;
      lock.lock() ;
      if(!pending_writes.empty())
        {
          pending_writes.front()();
          pending_writes.pop();
        }
      else
        can_write = true ;
      lock.unlock() ;
      } ;

  lock.lock() ;
  if(rec_endpoint == NULL)
    {
      if(can_write)
        {
          can_write = false ;
          increase_tasks();
          sock->async_send(buffers,sync_handler);
        }
      else
          pending_writes.push([this, sync_handler, buffers]()
                             {increase_tasks(); sock->async_send(buffers, sync_handler) ;});
    }
  else
    {
      if(can_write)
        {
          can_write = false ;
          increase_tasks();
          sock->async_send_to(buffers, *rec_endpoint, sync_handler) ;
        }
      else
        {
           //Use local variable because it shouldn't be a pointer in the capture (not valid when called)
           endpoint end_pt = *rec_endpoint ;
           pending_writes.push([this, sync_handler, end_pt, buffers]()
                             {increase_tasks(); sock->async_send_to(buffers,end_pt, sync_handler) ;});
        }
    }
  lock.unlock() ;
}

void ComunicatorImplem::decrease_tasks(){
  nb_tasks_mutex.lock() ;
  nb_tasks-- ;
  nb_tasks_mutex.unlock() ;
}

void ComunicatorImplem::increase_tasks(){
  nb_tasks_mutex.lock() ;
  nb_tasks++ ;
  nb_tasks_mutex.unlock() ;
}

