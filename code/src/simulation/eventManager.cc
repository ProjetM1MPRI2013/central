#include "eventManager.h" 
#include <type_traits>
#include <utility>
#include <boost/uuid/uuid_io.hpp>
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
        if (evt_info.el_info->location == nullptr) {
          DBG << "Found nullptr location, info_ptr: " << evt_info.el_info;
          if (--(evt_info.el_info->bound_events) <= 0) {
            delete evt_info.el_info;
          }
          listeners.erase(iterator++);
        } else {
          DBG << "Found " << evt_info.el_info->location->el_id << "'s location: " << evt_info.el_info->location << ", info_ptr: " << evt_info.el_info;
          evt_info.callback(evt_info.el_info->location, &source, arg);
          ++iterator;
        }
      }
    }
  }
}

void EventManager::listen(EventName event, EventSource& source, GenericEventListener& listener, event_callback run_callback) {

  if (listener.el_info->location == nullptr) {
    DBG << "recreate listener";
    if (listener.el_info->bound_events > 1) {
      listener.el_info->bound_events--;
      listener.el_info = new ListenerInfo{1,&listener};
    } else { // == 1
      listener.el_info->location = &listener;
    }
  }

  DBG << listener.el_id << " listens for source " << source.es_id << " giving ptr " << listener.el_info;

  auto resp = sources[source.es_id][event].insert({listener.el_id, EventInfo{listener.el_info, run_callback}});
  auto& evt_info = resp.first->second;
  auto& inserted = resp.second;

  if (inserted) {
    listener.el_info->bound_events++; 
  } else {
    if (evt_info.el_info->location == nullptr) {
      DBG << "was nullptr";
      if (--(evt_info.el_info->bound_events) <= 0) {
        DBG << "...and last holder: delete";
        delete evt_info.el_info;
      }
      listener.el_info->bound_events++; 
      evt_info.el_info = listener.el_info;
    }
    evt_info.callback = run_callback;
  }
}

void EventManager::markAsUnListened(listenerMap& listeners, GenericEventListener& listener) {
  auto it = listeners.find(listener.el_id);
  if (it != listeners.end()) {
    listener.el_info->bound_events--;
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
  // Equivalent to
  // if (--(...) <= 0) { delete ... ; new ... } else { ... = nullptr }
  if (listener.el_info->bound_events > 1) {
    DBG << "setting to nullptr";
    listener.el_info->location = nullptr;
  }
}

void EventManager::removeSource(EventSource& source) {
  auto it = sources.find(source.es_id);
  if (it != sources.end()) {
    for (auto& event_listeners : it->second) {
      for (auto& event_evt_info : event_listeners.second) {
        auto el_info = event_evt_info.second.el_info;
        el_info->bound_events--;
        if (el_info->bound_events <= 0 && el_info->location == nullptr) {
          delete el_info;
        }
      }
    }
    sources.erase(it);
  }
}

