#include "eventManager.h" 
targetMap EventManager::targets;

void EventManager::triggerEvent(EventName eventT, EventTarget& target) {
  try {
    auto listeners = targets.at(std::ref(target)).at(eventT);
    for (auto& pair : listeners) { pair.second(); };
  } catch (const std::out_of_range& e) {
    return;
  }
}
