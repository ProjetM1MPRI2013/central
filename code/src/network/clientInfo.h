#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

#include <string>

/**
 *
 * This class is used to discribe informations on the client used for the
 * connection with the server.
 *
 * Some field such as the local address, or
 * the local port of the connection will be filled automatically when connecting
 * to the server if they are not provided by the user.
 * Some other field may be added in the future such as the game version (to
 * ensure compatibity, player name ...)
 *
 * @author mheinric
 */

class ClientInfo {
  
public : 
  /**
   * Server address, will be used when connecting the client to the server.
   */
  std::string serverName ;

  /**
   * decimal representation of the port of the server to connect to.
   */
  std::string serverPort ;

  /**
   * The local address on the computer. By default, will be set during the
   * connection.
   */
  std::string localName ;
  std::string localPort ;

  /**
   * @brief ClientInfo : default constructors using default parameters
   */
  ClientInfo(){
    serverName = "localhost" ;
    serverPort = "1234" ;
    localName = "" ;
    localPort = -1 ;
  }

  /**
   * Create a new structure given the address of the server the client
   * will have to connect to.
   */
  ClientInfo(std::string& server_name, std::string port){
    serverName = server_name ;
    serverPort = port ;
    localName = "" ;
    localPort = -1 ;
  }

} ;

#endif
