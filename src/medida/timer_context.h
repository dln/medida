//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_TIMER_CONTEXT_H_
#define MEDIDA_TIMER_CONTEXT_H_

#include <chrono>
#include <memory>

namespace medida {

class Timer;

class TimerContext {
 public:
  TimerContext(Timer& timer);
  ~TimerContext();
  void Reset();
  std::chrono::nanoseconds Stop();
 private:
  class Impl;
  Impl* impl_;
  // std::unique_ptr<Impl> impl_;  // FIXME: y u incomplete type?!?
};

} // namespace medida

#endif // MEDIDA_TIMER_CONTEXT_H_
