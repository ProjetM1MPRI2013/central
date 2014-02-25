/**
 * @author: Adrien H.
 */
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "withUuid.h"
#include <boost/any.hpp>
#include "eventSource.h"
#include "genericEventListener.h"
#include <string>
#include <functional>
#include <type_traits>
#include <map>
#include <boost/uuid/uuid_io.hpp>

/**
 * How to use
 *
 * Events are just strings
 * To generate events, derive EventSource.
 * To listen to events, derive EventListener<YourDerivedClass>.
 */


template <typename T> using reference = std::reference_wrapper<T>;

typedef std::function<void (GenericEventListener*, EventSource*, boost::any)> event_callback;

struct EventInfo
{
  ListenerInfo* el_info; // use a shared_ptr instead of counting?
  event_callback callback;
};


/** We need a function from (source,type,listener) to callback,
 *  We create three maps : source_id -> (event -> (listener_id -> (int, listener*, callback)))
 */
typedef std::map<boost::uuids::uuid, EventInfo> listenerMap;
typedef std::map<EventName, listenerMap> eventMap;
typedef std::map<boost::uuids::uuid, eventMap> sourceMap;

/* Conditional template instanciation. Used for clarity in EventManager::triggerEvent.
 *
 * Consider E = enable_if<is_?<T>::value, B> 
 *
 * E::type will be B if T satisfies is_?.
 *
 * otherwise E::type won't exist, so template instanciation will fail.
 *
 * With this we can use one function if the argument is an lvalue and and another if it is an rvalue.
 */
template <typename T> using void_if_rvalue = typename std::enable_if<std::is_rvalue_reference<T&&>::value, void>::type;
template <typename T> using void_if_not_rvalue = typename std::enable_if<!std::is_rvalue_reference<T&&>::value, void>::type;

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
  static void listen(EventName event, EventSource& source, GenericEventListener& listener, event_callback callback);

  /**
   * @brief 'listener' stops listening from 'event' when triggered by 'source'.
   * @param event: event the listener stops listening from, for instance "panicBegins"
   * @param source: source generating the event, for instance a building, a zone or an NPC
   * @param listener: the listener that does not wish to be notified anymore
   *
   * The EventListener won't receive that specific Event from the simulation.
   *
   * To unlisten from an event source, pass the event source and the listener.
   * To unlisten from a type of event, pass only the event name and the listener.
   * To unlisten from all events, pass only the listener.
   */
  static void unlisten(EventName event, EventSource& source, GenericEventListener& listener);
  static void unlisten(EventSource& source, GenericEventListener& listener);
  static void unlisten(EventName event, GenericEventListener& listener);
  static void unlisten(GenericEventListener& listener);
  static void markAsUnListened(listenerMap& listeners, GenericEventListener& listener);

  /* Remove an event source from the event system. All listeners listening to source
   * immediately stop listening.
   */
  static void removeSource(EventSource& source);

  /* */
  template <typename ArgT>
  static void_if_rvalue<ArgT> triggerEvent(EventName event, EventSource& source, ArgT&& arg);
  template <typename ArgT>
  static void_if_not_rvalue<ArgT> triggerEvent(EventName event, EventSource& source, ArgT&& arg);

  static void triggerEvent(EventName event, EventSource& source, boost::any arg=boost::any{});

  static sourceMap sources;
};


/*
 * Implementations for EventManager
*/

template <typename ArgT>
void_if_rvalue<ArgT> EventManager::triggerEvent(EventName event, EventSource& source, ArgT&& arg) {
  EventManager::triggerEvent(event,source,boost::any(arg));
}

template <typename ArgT>
void_if_not_rvalue<ArgT> EventManager::triggerEvent(EventName event, EventSource& source, ArgT&& arg) {
  EventManager::triggerEvent(event,source,boost::any(std::ref(arg)));
}

/*
 * Implementations for EventSource
 */
template <typename ArgT>
void EventSource::trigger(EventName event, ArgT&& arg) {
  EventManager::triggerEvent(event, *this, std::forward<ArgT>(arg));
}

#endif
