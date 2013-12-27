#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "withUuid.h"
typedef std::string EventName;
#include <boost/any.hpp>
#include "eventSource.h"
#include <string>
#include <functional>
#include <map>

// Dummy generic class to store instances of EventListener<T>
// No one else may subclass GenericEventListener.
class GenericEventListener : public WithUuid {};

/** We need a function from (source,type,listener) to callback,
 *  We create three maps : source -> (event -> (listener -> callback))
 */
template <typename T> using reference = std::reference_wrapper<T>;
typedef std::map<reference<GenericEventListener>, std::function<void (boost::any)>, WithUuidCmp> listenerMap;
typedef std::map<EventName, listenerMap> eventMap;
typedef std::map<reference<EventSource>,eventMap, WithUuidCmp> sourceMap;

class EventManager {
  public:


  /**
   * @brief listen
   * @param eventT: event the listener listens to, for instance "isDestroyed"
   * @param source: source generating the event, for instance a building, a zone or an NPC
   * @param listener: the object inheriting from EventListener that wishes to be notified
   * @param callback: the method of listener that should be called when the event happens
   *
   * Any implementer of EventListener can listen to an event from the simulation. 
   * For every triple (EventName, EventSource, EventListener) there can be at most one event subscription.
   * Oversubscribing will erase the previous callback.
   *
   * To listen to all events from an EventSource, pass the empty EventName.
   * To listen to all events of type EventName, pass the empty EventSource.
   */
  static void listen(EventName event, EventSource& source, GenericEventListener& listener, std::function<void (boost::any)> callback);

  /**
   * @brief unlisten
   * @param eventT: event the listener stops listening from, for instance "panicBegins"
   * @param source: source generating the event, for instance a building, a zone or an NPC
   * @param listener: the listener that does not wish to be notified anymore
   *
   * The EventListener won't receive that specific Event from the simulation.
   *
   * To unlisten from all events from an EventSource, pass the empty EventName.
   * To unlisten from all events of a type, pass the empty EventSource
   */
  static void unlisten(EventName eventT, EventSource& source, GenericEventListener& listener);

  /* */
  template <typename ArgT>
  static void triggerEvent(EventName event, EventSource& source, ArgT& arg);
  static void triggerEvent(EventName event, EventSource& source, boost::any arg=boost::any{});

  static sourceMap sources;
};


/*
 * Implementations for EventManager
*/

template <typename ArgT>
void EventManager::triggerEvent(EventName event, EventSource& source, ArgT& arg) {
  EventManager::triggerEvent(event,source,boost::any(std::ref(arg)));
}
#endif
