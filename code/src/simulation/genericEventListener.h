/**
 * @author: Adrien H.
 */
#ifndef GENERIC_EVENT_LISTENER_H
#define GENERIC_EVENT_LISTENER_H

#include <boost/uuid/uuid.hpp>

class GenericEventListener;

/* Counts references to the GenericEventListener pointer
 * used by sources to trigger the event on the right listeners
 */
struct ListenerInfo {
  int bound_events;
  GenericEventListener* location;
};

/** 
 * Dummy generic class to store instances of EventListener<T>
 * No one else may subclass GenericEventListener.
 */

class GenericEventListener {
  private:
  boost::uuids::uuid el_id;
  ListenerInfo* el_info;
  friend class EventManager;
  friend class GenericEventListenerCmp;
  public:
  GenericEventListener();
  ~GenericEventListener();
  GenericEventListener(boost::uuids::uuid uuid);
  GenericEventListener(GenericEventListener&& other);
  GenericEventListener(GenericEventListener& other);
  GenericEventListener& operator=(GenericEventListener& other);
  GenericEventListener& operator=(GenericEventListener&& other);
};

struct GenericEventListenerCmp{
  bool operator()(const GenericEventListener& lhs, const GenericEventListener& rhs) const 
  {
    return lhs.el_id < rhs.el_id;
  }
};


#endif

