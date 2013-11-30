#include "simulation.h"
#include "eventListener.h"


// Templated functions must be defined in headers

template <typename TargetT>
void EventListener::subscribe(EventName eventT, TargetT& target, std::function<void (EventName, TargetT&)> callback) {
  simulation.subscribe(eventT, target, this, callback);
};

template <typename TargetT>
void EventListener::unsubscribe(EventName eventT, TargetT& target) {
  simulation.unsubscribe(eventT, target, this);
};
