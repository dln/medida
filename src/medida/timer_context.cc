//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/timer_context.h"

#include "medida/types.h"

namespace medida {

TimerContext::TimerContext(Timer& timer) 
    : timer_ (timer) {  // FIXME: GCC Bug 50025 - Uniform initialization of reference members broken
  Reset();
}

TimerContext::~TimerContext() {
  Stop();
}

void TimerContext::Reset() {
  start_time_ = Clock::now();
  active_ = true;
}

std::chrono::nanoseconds TimerContext::Stop() {
  if (active_) {
    auto dur = Clock::now() - start_time_;
    timer_.Update(dur);
    active_ = false;
    return dur;
  }
  return std::chrono::nanoseconds(0);
}


} // namespace medida