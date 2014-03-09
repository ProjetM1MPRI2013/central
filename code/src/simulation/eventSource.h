/**
 * @author: Adrien H.
 */
#ifndef EVENT_TARGET_H
#define EVENT_TARGET_H
#include "withUuid.h"

typedef std::string EventName;

/**
 * How to use:
 *
 * Once you've derived EventSource, you can just say trigger("myEvent")
 * or trigger("myEvent", 3).
 *
 * Everyone listening to "myEvent" from you (or from all) will receive the 
 * message if their callback is compatible: 
 * - if their callback takes no argument, their callback is compatible.
 * - if their callback takes an argument x of type X, their callback is
 *   compatible if the argument to trigger() supports implicit conversion to X.
 */
 
class EventSource {
  public: 
  friend class EventManager;
  friend struct EventSourceCmp;
  EventSource();
  EventSource(boost::uuids::uuid uuid);
  EventSource& operator=(const EventSource& other);
  EventSource& operator=(EventSource&& other);
  EventSource(EventSource&& other);
  EventSource(const EventSource& other);
  ~EventSource();


  void trigger(EventName event);
  template <typename ArgT>
  void trigger(EventName event, ArgT&& arg);
  private:
  boost::uuids::uuid es_id;
};

struct EventSourceCmp{
  bool operator()(const EventSource& lhs, const EventSource& rhs) const 
  {
    return lhs.es_id < rhs.es_id;
  }
};
#endif
