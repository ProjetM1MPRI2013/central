#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "withUuid.h"
typedef std::string EventName;
#include <boost/any.hpp>
#include "eventTarget.h"
#include <string>
#include <functional>
#include <map>

// Dummy generic class to store instances of EventListener<T>
// No one else may subclass GenericEventListener.
class GenericEventListener : public WithUuid {};

/** We need a function from (target,type,listener) to callback,
 *  We create three maps : target -> (type -> (listener -> callback))
 */
template <typename RefE> using reference = std::reference_wrapper<RefE>;
typedef std::map<reference<GenericEventListener>, std::function<void (boost::any)>, WithUuidCmp> listenerMap;
typedef std::map<EventName, listenerMap> eventMap;
typedef std::map<reference<EventTarget>,eventMap, WithUuidCmp> targetMap;

class EventManager {
  public:


  /**
   * @brief subscribe
   * @param eventT: event the listener subscribes to, for instance "isDestroyed"
   * @param target: target generating the event, for instance a building, a zone or an NPC
   * @param listener: the object inheriting from EventListener that wishes to be notified
   * @param callback: the method of listener that should be called when the event happens
   *
   * Any implementer of EventListener can listen to an event from the simulation. 
   * For every triple (EventName, EventTarget, EventListener) there can be at most one event subscription.
   * Oversubscribing will erase the previous callback.
   *
   * To subscribe to all events from an EventTarget, pass the empty EventName.
   * To subscribe to all events of type EventName, pass the empty EventTarget.
   */
  static void subscribe(EventName event, EventTarget& target, GenericEventListener& listener, std::function<void (boost::any)> callback);

  /**
   * @brief unsubscribe
   * @param eventT: event the listener unsubscribes from, for instance "panicBegins"
   * @param target: target generating the event, for instance a building, a zone or an NPC
   * @param listener: the listener that does not wish to be notified anymore
   *
   * The EventListener won't receive that specific Event from the simulation.
   *
   * To unsubscribe from all events from an EventTarget, pass the empty EventName.
   * To unsubscribe from all events of a type, pass the empty EventTarget
   */
  template <typename TargetT>
  static void unsubscribe(EventName eventT, TargetT& target, GenericEventListener& listener);

  /* */
  template <typename ArgT>
  static void triggerEvent(EventName event, EventTarget& target, ArgT& arg);
  static void triggerEvent(EventName event, EventTarget& target, boost::any arg=boost::any{});

  static targetMap targets;
};


/*
 * Implementations for EventManager
*/

template <typename TargetT>
void EventManager::unsubscribe(EventName eventT, TargetT& target, GenericEventListener& listener) {
  try {
    targets.at(std::ref(target)).at(eventT).erase(std::ref(listener));
  } catch (const std::out_of_range& e) {
    return;
  }
}

template <typename ArgT>
void EventManager::triggerEvent(EventName event, EventTarget& target, ArgT& arg) {
  EventManager::triggerEvent(event,target,boost::any(std::ref(arg)));
}
#endif
