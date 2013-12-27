#include "eventSource.h"
EventSource::EventSource() {}
EventSource::EventSource(boost::uuids::uuid uuid) : WithUuid(uuid) {}
