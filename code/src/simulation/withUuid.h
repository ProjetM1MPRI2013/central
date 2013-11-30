#ifndef WITH_UUID_H
#define WITH_UUID_H
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
// Event Manager templated functions use this,
// so they must be declared in headers
class WithUuid {
  public:
    WithUuid(): uuid(boost::uuids::random_generator()()) {}
    friend class WithUuidCmp;
  private:
    boost::uuids::uuid uuid;
};

struct WithUuidCmp{
    bool operator()(const WithUuid& lhs, const WithUuid& rhs) const 
    {
        return lhs.uuid<rhs.uuid;
    }
};
#endif
