#include "eventSource.h"
#include "eventManager.h"
#include <boost/uuid/uuid_io.hpp>

EventSource::EventSource() : es_id(WithUuid::generator()) {
}

EventSource::EventSource(boost::uuids::uuid uuid) : es_id(uuid) {
}

EventSource& EventSource::operator=(const EventSource& other) { 
  return *this;
}

// Both sources keep their IDs
EventSource& EventSource::operator=(EventSource&& other) { 
  if (this != &other) {
  }
  return *this;
}

EventSource::EventSource(const EventSource& other) : es_id(WithUuid::generator()) {
}

// New source gets old source's ID
EventSource::EventSource(EventSource&& other) : es_id(WithUuid::generator()) {
  this->es_id.swap(other.es_id); 
}

EventSource::~EventSource() {
  EventManager::removeSource(*this);
}

void EventSource::trigger(EventName event) {
  EventManager::triggerEvent(event, *this);
}
