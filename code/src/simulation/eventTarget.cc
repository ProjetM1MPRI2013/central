#include "eventTarget.h"
EventTarget::EventTarget() {}
EventTarget::EventTarget(boost::uuids::uuid uuid) : WithUuid(uuid) {}
