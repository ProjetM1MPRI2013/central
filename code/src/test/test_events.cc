//@author: Adrien H.
#include "main.h"
#include "test_events.h"
#include <boost/uuid/uuid_io.hpp>
#define DEBUG true
#include "debug.h"

namespace test {

  using namespace std;

  int test_number = 0;

  Mutable::Mutable(int v) {
    val = v;
  }

  Source::Source() : val(0) {}

  Listener::Listener() : EventListener<Listener>(), val(0) {
    listen("c", member, &Listener::eventHandler);
  }

  void Listener::eventHandler(Source& source, int arg) {
    LOG(debug) << "[l" << val << "] <- [s" << source.val << "] " << arg;
  }

  void Listener::eventHandlerMutable(Source& source, Mutable& arg) {
    LOG(debug) << "[l" << val << "] <- [s" << source.val << "] " << arg.val << "&  (setting to 1)";
    arg.val = 1;
  }

  void declare(std::string s) {
    LOG(debug) << s << " (" << ++test_number << ")";
  }

  void good(Listener& l, Source& s) {
    l.val = test_number;
    s.val = test_number;
  }

  int events() {
    Source s1;
    Listener l1;
    l1.listen("a",s1,&Listener::eventHandler);
    l1.listen("b",s1,&Listener::eventHandlerMutable);

    declare("Simple test");

    // Good means it's supposed to be sending/receiving events for this test.
    // at test i you should see [i] <- [i] i
    good(l1, s1); 
    s1.trigger("a",test_number);

    declare("Move-construct source");

    Source s2(std::move(s1));
    good(l1, s2);
    s2.trigger("a",test_number);

    declare("Move-assign source");

    Source s3;
    s3 = std::move(s2);
    good(l1, s2);
    s2.trigger("a", test_number);

    declare("Copy-construct source");
    Source s4(s2); 
    good(l1, s2);
    s2.trigger("a",test_number);
    s4.trigger("a",test_number);

    declare("Copy-assign source");
    s4 = s2; 
    good(l1, s2);
    s2.trigger("a",test_number);
    s4.trigger("a",test_number);

    declare("Move-construct listener");

    Listener l2(std::move(l1));
    good(l2, s2);
    s2.trigger("a",test_number);

    declare("Move-assign listener");

    Listener l3 = std::move(l2);
    good(l3, s2);
    s2.trigger("a",test_number);

    declare("Copy-construct listener");
    Listener l4(l3);
    good(l3, s2);
    s2.trigger("a",test_number);

    declare("Copy-assign listener");
    l4 = l3; 
    good(l3,s2);
    s2.trigger("a",test_number);

    declare("Move source after move listener");
    Source s5(std::move(s2));
    good(l3, s5);
    s5.trigger("a",test_number);

    declare("Mutable value");
    Mutable m(test_number);
    good(l3,s5);
    s5.trigger("b",m);
    LOG(debug) << "Found: " << m.val;

    declare("Simple member");
    Listener l5;
    good(l5,l5.member);
    l5.member.trigger("c",test_number);

    declare("Move-construct listener, member triggers");
    Listener l6(std::move(l5));
    good(l6,l6.member);
    l6.member.trigger("c",test_number);

    declare("Move-assign listener, member triggers");
    Listener l7 = std::move(l6);
    good(l7,l7.member);
    l7.member.trigger("c",test_number);

    declare("Move-assign member");
    l7.member = Source();
    good(l7,l7.member);
    l7.member.trigger("c",test_number);
    //a1.member = Source();

    declare("Reference counting #1");
    good(l3,s5);
    s5.trigger("a",test_number);
    EventManager::unlisten(l3);

    declare("Unlisten then listen");
    good(l3,s5);
    l3.listen("a",s5,&Listener::eventHandler);
    s5.trigger("a",test_number);

    declare("Unlisten, remove source, listen");
    Source s6;
    good(l3,s6);
    EventManager::unlisten(l3);
    EventManager::removeSource(s5);
    l3.listen("a",s6,&Listener::eventHandler);
    s6.trigger("a",test_number);



    LOG(debug) << "[fin]";

    return 0;
    /*
    Source source = Source();
    Listener listener = Listener();

    // Setting up listening events and arguments
    listener.listen("eventA",source,&Listener::eventHandler);
    listener.listen("eventB",source,&Listener::eventHandlerMutable);
    Mutable m = Mutable(0);

    LOG(debug) << "Simple test";
    source.trigger("eventA",0);
    LOG(debug);

    LOG(debug) << "Mutable test";
    LOG(debug) << "Triggering event on an lvalue. It will be passed by reference.";
    LOG(debug) << "Mutable value is: " << m.val;
    int old_value = m.val;
    LOG(debug) << "Triggering event. This should change the original value.";
    source.trigger("eventB",m);
    LOG(debug) << "Mutable value is: " << m.val;
    LOG(debug);

    LOG(debug) << "Copy assignment tests";
    Listener a1,a2;
    // Assign member
    //a1.member = Source();
    std::cout << "a1\n  el_uid: " << a1.event_listener_uuid << "\n  ms_uid: " << a1.member.event_source_uuid << std::endl;
    a1.member.trigger("eventC", 1);
    Listener a3;
    a3 = std::move(a1);
    std::cout << "a3\n el_uid: " << a3.event_listener_uuid << "\n ms_uid: " << a3.member.event_source_uuid << std::endl;
    a3.member.trigger("eventC",10);
    // Assign listener
    //a2 = a1;
    //a2.member.trigger("eventC", 2);
    // Copy listener
    //Listener a3(a2);
    //a3.member.trigger("eventC", 3);
    //LOG(debug);

    LOG(debug) << "Move assignment test";
    list<Listener> list;
    list.push_back(std::move(Listener()));
    list.front().member.trigger("eventC", 4);
 

    if (old_value == m.val) return 0;
    else return 1;
    */
  }
}
