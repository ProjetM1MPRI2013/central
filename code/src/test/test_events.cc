//@author: Adrien H.
#include "main.h"
#include "test_events.h"
#define DEBUG true
#include "debug.h"

namespace test {

  using namespace std;

  Mutable::Mutable(int v) {
    val = v;
  }

  void Listener::eventHandler(Source& source, int arg) {
    LOG(debug) << "  Inside listener: received eventA from source with argument " << arg;
  }

  void Listener::eventHandlerMutable(Source& source, Mutable& arg) {
    LOG(debug) << "  Inside listener: Received eventB from source with mutable argument " << arg.val;
    LOG(debug) << "  Inside listener: Changing mutable value to 1";
    arg.val = 1;
  }

  int events() {
    Source source = Source();
    Listener listener = Listener();

    // Setting up listening events and arguments
    listener.listen("eventA",source,&Listener::eventHandler);
    listener.listen("eventB",source,&Listener::eventHandlerMutable);
    Mutable m = Mutable(0);

    LOG(debug) << "Triggering event on an rvalue. It will be passed by value.";
    source.trigger("eventA",42);
    LOG(debug);

    LOG(debug) << "Triggering event on an lvalue. It will be passed by reference.";
    LOG(debug) << "Mutable value is: " << m.val;
    int old_value = m.val;
    LOG(debug) << "Triggering event. This should change the original value.";
    source.trigger("eventB",m);
    LOG(debug) << "Mutable value is: " << m.val;

    if (old_value == m.val) return 0;
    else return 1;
  }
}
