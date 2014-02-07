/**
 * @author: Adrien H., Joseph
 */
#include "withUuid.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
// Event Manager templated functions use this,
// so they must be declared in headers

// Fix valgrind errors on non-intialized random numbers.
// Otherwise, default initialization would work with
// boost::uuids::random_generator()()
// in the constructor.
// See https://svn.boost.org/trac/boost/ticket/7248
//
boost::mt19937 seed;
boost::uuids::random_generator WithUuid::generator = boost::uuids::random_generator(seed);

boost::uuids::uuid WithUuid::getUuid() const {
  return uuid;
}

void WithUuid::setUuid(boost::uuids::uuid id) {
  uuid = id;
  return;
}

WithUuid::WithUuid(boost::uuids::uuid uuid) {
  this->uuid = uuid;
  return;
}
