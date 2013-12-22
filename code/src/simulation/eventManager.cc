#include "eventManager.h" 
targetMap EventManager::targets;

void EventManager::triggerEvent(EventName event, EventTarget& target, boost::any arg) {
  try {
    auto listeners = targets.at(target).at(event);
    for (auto& pair : listeners) { pair.second(arg); };
  } catch (const std::out_of_range& e) {
    return;
  }
}

