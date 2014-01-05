#ifndef WITH_UUID_H
#define WITH_UUID_H
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

/**
 * @brief The WithUuid class
 * It only contains a uuid,
 * any class which needs a uuid should be a subclass of WithUuid
 */
class WithUuid {
  private:
    boost::uuids::uuid uuid;

 protected:
    void setUuid(boost::uuids::uuid id);

  public:
    // Event Manager templated functions use this,
    // so they must be declared in headers
    /**
     * @brief WithUuid
     * Creates a new WithUuid object, the uuid is generated randomly by boost
     */
    WithUuid(): uuid(boost::uuids::random_generator()()) {}

    /**
     * @brief WithUuid
     * Creates a new WithUuid object, with a given uuid
     * @param uuid: the uuid
     */
    WithUuid(boost::uuids::uuid uuid);

    friend class WithUuidCmp;
    
    /**
     * @brief getUuid
     * @return the uuid
     */
    boost::uuids::uuid getUuid();
};



/**
 * @brief A comparator for the WithUuid class
 */
class WithUuidCmp{
 public:
    bool operator()(const WithUuid& lhs, const WithUuid& rhs) const 
    {
        return lhs.uuid<rhs.uuid;
    }
};
#endif
