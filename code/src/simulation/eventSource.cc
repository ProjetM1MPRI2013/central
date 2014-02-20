#include "eventSource.h"
#include "eventManager.h"

EventSource::EventSource() {}
// WARNING Since WithUuid is a *virtual* base class of EventSource,
// the WithUuid constructor will *not* be called if you subclass EventSource
// and call EventSource(uuid) in your initialization list.
// You'll have to *also* call WithUuid(uuid).
EventSource::EventSource(boost::uuids::uuid uuid) : WithUuid(uuid) {}
EventSource::~EventSource() {
  EventManager::remove(*this);
}

void EventSource::trigger(EventName event) {
  EventManager::triggerEvent(event, *this);
}
