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

