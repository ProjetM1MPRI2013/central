#include "eventSource.h"
#include "eventManager.h"

EventSource::EventSource() {}
EventSource::EventSource(boost::uuids::uuid uuid) : WithUuid(uuid) {}
EventSource::~EventSource() {
  EventManager::remove(*this);
}

void EventSource::trigger(EventName event) {
  EventManager::triggerEvent(event, *this);
}
