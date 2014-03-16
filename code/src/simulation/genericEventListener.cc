#include "genericEventListener.h"
#include "eventManager.h"
using namespace std;
/* Note: If all that memory allocation becomes a problem,
 * it is entirely possible to add another state where
 * el_info == nullptr
 * so that zero memory is allocated until a listener starts listening.
 * Note to self: see local git branch wipevent
 */

GenericEventListener::GenericEventListener() : 
  el_id(WithUuid::generator()),
  el_info(new ListenerInfo{1,this})
{
}

GenericEventListener::GenericEventListener(boost::uuids::uuid uuid) : 
  el_id(uuid),
  el_info(new ListenerInfo{1,this})
{
}

GenericEventListener::GenericEventListener(GenericEventListener& other) : 
  el_id(WithUuid::generator()),
  el_info(new ListenerInfo{1,this}) 
{
}

GenericEventListener::GenericEventListener(GenericEventListener&& other) :
  el_info(other.el_info)
{
  if (el_info->location != nullptr) {
    el_info->location = this;
  }
  other.el_info = new ListenerInfo{1,&other};
  el_id.swap(other.el_id);
}

GenericEventListener& GenericEventListener::operator=(GenericEventListener& other) { 
  return *this; 
}

GenericEventListener& GenericEventListener::operator=(GenericEventListener&& other) { 
  if (this != &other) {
    std::swap(el_info,other.el_info);
    if (el_info->location != nullptr) {
      el_info->location = this;
    }
    if (other.el_info->location != nullptr) {
      other.el_info->location = &other;
    }
    el_id.swap(other.el_id); 
  }
  return *this;
}

GenericEventListener::~GenericEventListener() {
  if (--(el_info->bound_events) <= 0) {
    delete el_info;
  } else {
    el_info->location = nullptr;
  }
}
