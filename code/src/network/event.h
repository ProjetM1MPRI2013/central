#ifndef EVENT_H
#define EVENT_H
#include<string>

/**
 * @brief The Event class
 * Temporary will be replaced by a class from scenario/
 * simulation
 */

class Event
{
public:
    Event();
    std::string& toString(){
        std::string *s = new std::string() ;
        return *s ;
    }
};

#endif // EVENT_H
