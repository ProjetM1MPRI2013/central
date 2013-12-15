#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "withUuid.h"
typedef std::string EventName;
#include "eventListener.h"
#include "eventTarget.h"
#include <string>
#include <functional>
#include <map>

  /** We need a function from (target,type,listener) to callback,
   *  We create three maps : target -> (type -> (listener -> callback))
   */
  template <typename RefE> using reference = std::reference_wrapper<RefE>;
  typedef std::map<reference<EventListener>, std::function<void ()>, WithUuidCmp> listenerMap;
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
  template <typename TargetT>
  static void subscribe(EventName eventT, TargetT& target, EventListener& listener, std::function<void (EventName, TargetT&)> callback);

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
  static void unsubscribe(EventName eventT, TargetT& target, EventListener& listener);

  /* */
  static void triggerEvent(EventName eventT, EventTarget& target);

  static targetMap targets;
};

/* Subscribe and unsubscribe implementation in header because of the template */

template <typename TargetT>
void EventManager::subscribe(EventName event, TargetT& target, EventListener& listener, std::function<void (EventName, TargetT&)> callback) {
  /* Wrapping in a lambda to avoid type issues. The template ensures type safety. */
  /* Implementation note: we could create the lambda in the EventListener but
   * we may want to pass additional values to the callback in the future */
  auto run_callback = [callback,event,&target]() { callback(event,target); };
  targets[target][event][listener] = run_callback;
}

template <typename TargetT>
void EventManager::unsubscribe(EventName eventT, TargetT& target, EventListener& listener) {
  try {
    targets.at(std::ref(target)).at(eventT).erase(std::ref(listener));
  } catch (const std::out_of_range& e) {
    return;
  }
}

template <typename TargetT>
void EventListener::subscribe(EventName eventT, TargetT& target, std::function<void (EventName, TargetT&)> callback) {
  EventManager::subscribe(eventT, target, *this, callback);
};

template <typename TargetT>
void EventListener::unsubscribe(EventName eventT, TargetT& target) {
  EventManager::unsubscribe(eventT, target, *this);
};
#endif
