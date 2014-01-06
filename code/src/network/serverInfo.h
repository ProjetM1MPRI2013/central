#ifndef SERVER_INFO_H
#define SERVER_INFO_H


#include<string>

/**
 * Class used to represent informations on the server. These informations will
 * be used to create the server, and during the connexions of the clients.
 * Other fields can be added in the future such as the game version, the name of
 * the server ...
 */

class ServerInfo {
public :
  /**
   * The address the server will be using to listen for connexions.
   */
  std::string hostname ;
  std::string port ;

  /**
   * @brief ServerInfo
   * Creates a new instace, using a default adress.
   */
  ServerInfo(){
     hostname = "localhost" ;
     port = "1234" ;
  }
} ;

#endif
