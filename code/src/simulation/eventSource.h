#ifndef EVENT_TARGET_H
#define EVENT_TARGET_H
#include "withUuid.h"
class EventSource : public WithUuid {
  public: 
  EventSource();
  EventSource(boost::uuids::uuid uuid);
};
#endif

