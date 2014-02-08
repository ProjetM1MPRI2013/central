#ifndef TEST_EVENTS_H
#define TEST_EVENTS_H
#include "eventManager.h"
#include "eventListener.h"
#include "eventSource.h"
namespace test {

  class Mutable {
    public:
      Mutable(int);
      int val;
  };

  class Source : public EventSource {
  };

  class Listener : public EventListener<Listener> {
    public:
      void eventHandler(Source& source, int arg);
      void eventHandlerMutable(Source& source, Mutable& arg);
  };

  int events ();

}
#endif
