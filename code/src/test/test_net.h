#ifndef TEST_NET
#define TEST_NET

#include <abstractMessage.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

/*
 * Test functions for the network part.
 * @author mheinric
 */

namespace test {
  int net_dummy() ;

  int net_real() ;

  int net_serialization() ;

  class TestC {
  public :
    int data = 0 ;
    //Virtual method so that class is considered base
    virtual void nill() {}
    virtual ~TestC(){}

  private :
    //Serialization

    friend class boost::serialization::access ;

    template <class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar & data ;
    }

  };


  class TestD : public TestC {
  public :
    int data2 = 0;
    SIMPLE_MESSAGE(TestD, TestC, data2)
  };

  class TestA : public AbstractMessage {
  public :
    TestA() : data(0){}
    TestA(int t){
      data = t ;
    }

    virtual AbstractMessage* copy() {
      return new TestA(*this) ;
    }

    int data ;
    int data2 ;

    SIMPLE_MESSAGE(TestA, AbstractMessage, data, data2)
  };

  class TestB : public AbstractMessage {
  public :
    TestB(): data(0){
    }

    TestB(int t){
      data = t ;
    }

    virtual AbstractMessage* copy() {
      return new TestB(*this) ;
    }

    int data ;

    SIMPLE_MESSAGE(TestB, AbstractMessage, data)
  };


}
BOOST_CLASS_EXPORT_KEY(test::TestA)
BOOST_CLASS_EXPORT_KEY(test::TestB)

#endif
