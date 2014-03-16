#include "eventManager.h" 
#include <type_traits>
#include <utility>
#include <boost/uuid/uuid_io.hpp>
#include <memory>
#define DEBUG false
#include "debug.h"

using namespace std;

thread_local sourceMap EventManager::sources;

void EventManager::triggerEvent(EventName event, EventSource& source, boost::any arg) {
  DBG << "triggering on source";
  auto it1 = sources.find(source.es_id);
  if (it1 != sources.end()) {
    auto it2 = it1->second.find(event);
    if (it2 != it1->second.end()) {
      auto& listeners = it2->second;
      auto iterator = listeners.begin();
      while (iterator != listeners.end()) {
        auto& evt_info = iterator->second;
        if (*evt_info.el_ptr == nullptr) {
          DBG << "Found nullptr location";
          listeners.erase(iterator++);
        } else {
          DBG << "Found " << (*evt_info.el_ptr)->el_id << "'s location: " << *evt_info.el_ptr;
          evt_info.callback(*evt_info.el_ptr, &source, arg);
          ++iterator;
        }
      }
    }
  }
}

void EventManager::listen(EventName event, EventSource& source, GenericEventListener& listener, event_callback run_callback) {

  if (*listener.el_ptr == nullptr) {
    DBG << "recreate listener";
    if (listener.el_ptr.unique()) {
      *listener.el_ptr = &listener;
    } else {
      listener.el_ptr = make_shared<GenericEventListener*>(&listener);
    }
  }

  DBG << listener.el_id << " listens for source " << source.es_id << " giving ptr " << listener.el_ptr;

  auto resp = sources[source.es_id][event][listener.el_id] = EventInfo{listener.el_ptr, run_callback};
}

void EventManager::markAsUnListened(listenerMap& listeners, GenericEventListener& listener) {
  auto it = listeners.find(listener.el_id);
  if (it != listeners.end()) {
    listeners.erase(it);
  }
}

void EventManager::unlisten(EventName eventT, EventSource& source, GenericEventListener& listener) {
  auto it1 = sources.find(source.es_id);
  if (it1 != sources.end()) {
    auto it2 = it1->second.find(eventT);
    if (it2 != it1->second.end()) {
      markAsUnListened(it2->second, listener);
    }
  }
}

// FIXME slow
void EventManager::unlisten(EventSource& source, GenericEventListener& listener) {
  auto it = sources.find(source.es_id);
  if (it != sources.end()) {
    for (auto& event_listeners : it->second) {
      markAsUnListened(event_listeners.second, listener);
    }
  }
}

// FIXME slow
void EventManager::unlisten(EventName event, GenericEventListener& listener) {
  for (auto& source_events : sources) {
    auto it = source_events.second.find(event);
    if (it != source_events.second.end()) {
      markAsUnListened(it->second, listener);
    }
  }
}

void EventManager::unlisten(GenericEventListener& listener) {
  if (!(listener.el_ptr.unique())) {
    DBG << "setting to nullptr";
    *listener.el_ptr = nullptr;
  }
}

void EventManager::removeSource(EventSource& source) {
  auto it = sources.find(source.es_id);
  if (it != sources.end()) {
    sources.erase(it);
  }
}
