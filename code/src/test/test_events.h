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
    public:
    Source();
    int val;
  };

  class Listener : public EventListener<Listener> {
    public:
      Listener();
      Listener(Listener& other) = default;
      Listener(Listener&& other) = default;
      Listener& operator=(Listener& other) = default;
      Listener& operator=(Listener&& other) = default;
      Source member;
      int val;
      void eventHandler(Source& source, int arg);
      void eventHandlerMutable(Source& source, Mutable& arg);
  };

  int events ();

}
#endif
