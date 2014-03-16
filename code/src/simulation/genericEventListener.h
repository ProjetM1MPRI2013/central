/**
 * @author: Adrien H.
 */
#ifndef GENERIC_EVENT_LISTENER_H
#define GENERIC_EVENT_LISTENER_H

#include <boost/uuid/uuid.hpp>
#include <memory>

class GenericEventListener;

/** 
 * Dummy generic class to store instances of EventListener<T>
 * No one else may subclass GenericEventListener.
 */

class GenericEventListener {
  private:
  boost::uuids::uuid el_id;
  std::shared_ptr<GenericEventListener*> el_ptr;
  friend class EventManager;
  friend struct GenericEventListenerCmp;
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
