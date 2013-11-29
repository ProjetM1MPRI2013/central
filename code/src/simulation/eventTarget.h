#ifndef EVENT_TARGET_H
#define EVENT_TARGET_H
class IdCarrier {
  public:
    int id;
  //IdCarrier() {
    //id = rand();
  //}
};

class EventTarget : public IdCarrier {
  //bool operator< (const EventTarget& x) {
    //id < x.id;
  //}
};

struct IdCarrierCmp{
    bool operator()(const IdCarrier& lhs, const IdCarrier& rhs) const 
    {
        return lhs.id<rhs.id;
    }
};
#endif

