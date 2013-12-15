#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "withUuid.h"

/**
 * @brief EventListeners may subscribe to events generated by the Simulation
 */

class EventListener : public WithUuid {

public :
 	 /**
     * @brief subscribe to events of type eventT on target using callback
     * @param eventT: type of event being subscribed to (can be empty)
     * @param target: object the event is about
     * @param callback: a method of the instance inheriting from EventListener 
    */
    template <typename TargetT>
    void subscribe(EventName eventT, TargetT& target, std::function<void (EventName, TargetT&)> callback);

    /**
     * @brief unsubscribe to events of type eventT on target
     */
    template <typename TargetT>
    void unsubscribe(EventName eventT, TargetT& target);

    //bool operator< (const EventListener& x);
};


#endif // EVENT_LISTENER_H
