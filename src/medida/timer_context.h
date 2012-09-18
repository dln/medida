//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_TIMER_CONTEXT_H_
#define MEDIDA_TIMER_CONTEXT_H_

#include <chrono>
#include <cstdint>

#include "medida/timer.h"

namespace medida {

class TimerContext {
public:
  TimerContext(Timer& timer);
  ~TimerContext();
  void Reset();
  std::chrono::nanoseconds Stop();
protected:
  Clock::time_point start_time_;
  Timer& timer_;
  bool active_;
};

} // namespace medida

#endif // MEDIDA_TIMER_CONTEXT_H_
