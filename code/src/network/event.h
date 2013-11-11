#ifndef EVENT_H
#define EVENT_H
#include<string>

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
