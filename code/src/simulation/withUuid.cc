#include "withUuid.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
// Event Manager templated functions use this,
// so they must be declared in headers

boost::uuids::uuid WithUuid::getUuid() {
  return uuid;
}
