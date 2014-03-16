#include "genericEventListener.h"
#include "eventManager.h"
#include <memory>
using namespace std;
/* Note: If all that memory allocation becomes a problem,
 * it should be possible to add another state where
 * el_ptr == nullptr
 * so that zero memory is allocated until a listener starts listening.
 */

GenericEventListener::GenericEventListener() : 
  el_id(WithUuid::generator()),
  el_ptr(make_shared<GenericEventListener*>(this)) 
{
}

GenericEventListener::GenericEventListener(boost::uuids::uuid uuid) : 
  el_id(uuid),
  el_ptr(make_shared<GenericEventListener*>(this)) 
{
}

GenericEventListener::GenericEventListener(GenericEventListener& other) : 
  el_id(WithUuid::generator()),
  el_ptr(make_shared<GenericEventListener*>(this)) 
{
}

GenericEventListener::GenericEventListener(GenericEventListener&& other) :
  el_ptr(other.el_ptr)
{
  if (*el_ptr != nullptr) {
    (*el_ptr) = this;
  }
  other.el_ptr = make_shared<GenericEventListener*>(this);
  el_id.swap(other.el_id);
}

GenericEventListener& GenericEventListener::operator=(GenericEventListener& other) { 
  return *this; 
}

GenericEventListener& GenericEventListener::operator=(GenericEventListener&& other) { 
  if (this != &other) {
    std::swap(el_ptr,other.el_ptr);
    if (*el_ptr != nullptr) {
      *el_ptr = this;
    }
    if (*other.el_ptr != nullptr) {
      *other.el_ptr = &other;
    }
    el_id.swap(other.el_id); 
  }
  return *this;
}

GenericEventListener::~GenericEventListener() {
  *el_ptr = nullptr;
}
