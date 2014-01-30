/**
   @author: Adrien K.
 */


#ifndef NEWMOV_H
#define NEWMOV_H

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "network/abstractMessage.h"

enum NewMov {P_RIGHT, P_LEFT, P_UP, P_DOWN, R_RIGHT, R_LEFT, R_UP, R_DOWN};

void printNewMov(NewMov nm);

class NewMovNetwork : public AbstractMessage {
 public:
  NewMov movement;
  int playerID;
  NewMovNetwork(NewMov m, int pid);

  //AbstractMessage functions
  static std::string getMsgType();
  virtual std::string toString();
  static NewMovNetwork* fromString(std::string& msg);
  virtual AbstractMessage* copy();

private :
  //Serialization

  NewMovNetwork() ;

  friend class boost::serialization::access ;

  template <class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & movement ;
    ar & playerID ;
  }
};

#endif
