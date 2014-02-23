#include "eventManager.h" 
sourceMap EventManager::sources;

void EventManager::triggerEvent(EventName event, EventSource& source, boost::any arg) {
  try {
    auto listeners = sources.at(source).at(event);
    for (auto& pair : listeners) { pair.second(arg); };
  } catch (const std::out_of_range& e) {
    return;
  }
}

void EventManager::listen(EventName event, EventSource& source, GenericEventListener& listener, std::function<void (boost::any)> run_callback) {
  sources[source][event][listener] = run_callback;
}

void EventManager::unlisten(EventName eventT, EventSource& source, GenericEventListener& listener) {
  try {
    sources.at(std::ref(source)).at(eventT).erase(std::ref(listener));
  } catch (const std::out_of_range& e) {
    return;
  }
}

void EventManager::unlisten(EventSource& source, GenericEventListener& listener) {
  try {
    for (auto& event_listeners : sources.at(std::ref(source))) {
      event_listeners.second.erase(std::ref(listener));
    }
  } catch (const std::out_of_range& e) {
    return;
  }
}

void EventManager::unlisten(EventName event, GenericEventListener& listener) {
  for (auto& source_events : sources) {
    try {
      source_events.second.at(event).erase(std::ref(listener));
    } catch (const std::out_of_range& e) {
      return;
    }
  }
}

// FIXME very expensive
void EventManager::unlisten(GenericEventListener& listener) {
  for (auto& source_events : sources) {
    for (auto& event_listeners : source_events.second) {
      try {
        event_listeners.second.erase(std::ref(listener));
      } catch (const std::out_of_range& e) {
        return;
      }
    }
  }
}

void EventManager::remove(EventSource& source) {
  auto it = sources.find(source);
  if (it != sources.end() && &(source) == &(it->first.get())) { // Making sure we're the right guy
    sources.erase(std::ref(source));
  }
}

