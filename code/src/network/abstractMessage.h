#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include <boost/serialization/export.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <string>
#include <assert.h>

/**
 * @brief The AbstractMessage class
 * This calss defines an interface which messages sent over
 * the network must respect.
 *
 * All the methods of this class should be overridden in children
 * classes (including static ones). Any class that implements this
 * interface can be used to call receiveMessages<MsgType>() and
 * sendMessage<MsgType>(message).
 *
 * @author mheinric
 */
class AbstractMessage {
public :
  /**
   * @brief getMsgType
   * @return a string object representing the Class of a message
   *
   * Every class extending the AbstractMessageInterface must
   * provide their own implementation of the getMsgType method.
   * The returned string must be exactly 8 characters long.
   * (it will be sent over the network, so a fixed size is required).
   */
  static std::string getMsgType() { return "AbstrMsg" ; }

  /**
   * @brief toString : serialize the object.
   * @return The string representation of this message
   */
  virtual std::string toString() ;

  /**
   * @brief fromString : function used for deserialisation
   * @param msg : the string representation of the message
   * @return The message created from its representation
   * All classes inherited from AbstractMessage should implement
   * the function fromString with the signature :
   * static MsgType * fromString(std::string)
   */
  static AbstractMessage * fromString(const std::string& msg) ;

  /**
   * @brief copy : copy the message
   * @return a new instance of the message, containing the same data
   */
  virtual AbstractMessage* copy() =0 ;

  virtual ~AbstractMessage(){ }

private :
  //Serialization
  friend class boost::serialization::access ;

  template <class Archive>
  void serialize(Archive & ar, const unsigned int version){}

};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(AbstractMessage)

/*******************************************
 *Templates used for a simple serialization*
 *******************************************/

template<class Archive>
void __serialize_variables(Archive& ar) {
}

template<class Archive, typename T, typename... Types >
void __serialize_variables(Archive& ar, T& var, Types&... rest) {
  ar & var ;
  __serialize_variables(ar, rest...) ;
}

#define SIMPLE_SERIALIZATION(vars...) \
private :                    \
  friend class boost::serialization::access ;  \
  template <class Archive>                    \
  void serialize(Archive & ar, const unsigned int version)  \
  {                                                         \
    __serialize_variables(ar, ## vars) ;   \
  }              \


#define SIMPLE_SERILAIZATION_DERIVED(BaseClass, vars...) \
  private :                    \
    friend class boost::serialization::access ;  \
    template <class Archive>                    \
    void serialize(Archive & ar, const unsigned int version)  \
    {                                                         \
      ar & boost::serialization::base_object<BaseClass>(*this); \
      __serialize_variables(ar, ## vars) ;   \
    }              \

#define SIMPLE_MESSAGE(ClassName, BaseClass, vars...) \
  public : \
  static std::string getMsgType() { std::string s = std::string(#ClassName) ; s.resize(8) ; return s ;} \
  SIMPLE_SERILAIZATION_DERIVED(BaseClass, ## vars) \

#endif // ABSTRACTMESSAGE_H
