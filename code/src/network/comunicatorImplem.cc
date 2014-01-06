#include "comunicatorImplem.h"

using namespace std ;
using namespace boost::asio ;

ComunicatorImplem::ComunicatorImplem() : last_sent(0), ack_set(), received_messages(), sent_ack(){
  //init fields
  service = new io_service() ;
  sock = new ip::udp::socket(*service) ;
  buff = new string(BUFF_SIZE, '\000') ;
  header_buff = new string(HEADER_SIZE, '\000') ;
}

ComunicatorImplem::~ComunicatorImplem(){
  shutdown() ;
  delete service ;
  delete sock ;
  delete buff ;
  delete header_buff ;
}

void ComunicatorImplem::shutdown(){
  service->stop();
  sock->shutdown(ip::udp::socket::shutdown_both);
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
  received_messages[NetEvent::getMsgType()].push_back(&event.toString()) ;
}

bool ComunicatorImplem::ack_message(const string &header) {
  assert(header.size() == HEADER_SIZE) ;
  return (header[HEADER_SIZE -1] != '\00') ;
}

std::string* ComunicatorImplem::create_header(bool reliable, std::string type, int id) {
  assert(type.size() == 8) ;
  string * header = new string(HEADER_SIZE, '\00') ;
  if(reliable)
    header[HEADER_SIZE -1] = '\001' ;
  int i ;
  for(i = 0 ; i < 8; i++)
    {
      header[i] = type[i] ;
    }
  header[8] = (char) id % 256 ;
  header[9] = (char) (id/256) % 256 ;
  header[10] = (char) (id/256/256) % 256 ;
  header[11] = (char) (id/256/256/256) % 256 ;

  return header ;
}


