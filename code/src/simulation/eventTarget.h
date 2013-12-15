#ifndef EVENT_TARGET_H
#define EVENT_TARGET_H
#include "withUuid.h"
class EventTarget : public WithUuid {
  public: 
  EventTarget();
  EventTarget(boost::uuids::uuid uuid);
};
#endif

