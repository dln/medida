//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/timer.h"

#include "medida/timer_context.h"

namespace medida {

Timer::Timer(std::chrono::nanoseconds duration_unit, std::chrono::nanoseconds rate_unit) 
    : duration_unit_       {duration_unit},
      duration_unit_nanos_ {duration_unit.count()},
      rate_unit_           {rate_unit},
      meter_               {"calls", rate_unit},
      histogram_           {SamplingInterface::kBiased} {
}


Timer::~Timer() {
}


std::chrono::nanoseconds Timer::duration_unit() const {
  return duration_unit_;
}


std::chrono::nanoseconds Timer::rate_unit() const {
  return rate_unit_;
}


std::uint64_t Timer::count() const {
  return histogram_.count();
}


double Timer::min() const {
  return histogram_.min() / duration_unit_nanos_;
}


double Timer::max() const {
  return histogram_.max() / duration_unit_nanos_;
}


double Timer::mean() const {
  return histogram_.mean() / duration_unit_nanos_;
}


double Timer::std_dev() const {
  return histogram_.std_dev() / duration_unit_nanos_;
}


double Timer::sum() const {
  return histogram_.sum() / duration_unit_nanos_;
}


std::string Timer::event_type() const {
  return meter_.event_type();
}


double Timer::fifteen_minute_rate() {
  return meter_.fifteen_minute_rate();
}


double Timer::five_minute_rate() {
  return meter_.five_minute_rate();
}


double Timer::one_minute_rate() {
  return meter_.one_minute_rate();
}


double Timer::mean_rate() {
  return meter_.mean_rate();
}


void Timer::Process(const MetricProcessor& processor) const  {
  processor.Process(*this);
}


void Timer::Clear() {
  return histogram_.Clear();
}


void Timer::Update(std::chrono::nanoseconds duration) {
  auto count = duration.count();
  if (count >= 0) {
    histogram_.Update(count);
    meter_.Mark();
  }
}


stats::Snapshot Timer::GetSnapshot() const {
  auto values = histogram_.GetSnapshot().getValues();
  std::vector<double> converted;
  converted.reserve(values.size());
  for (auto& v : values) {
    converted.push_back(v / (double)duration_unit_nanos_);
  }
  return {std::begin(converted), std::end(converted)};
}


TimerContext Timer::TimeScope() {
  return {*this};
}


void Timer::Time(std::function<void()> func) {
  auto t = TimeScope();
  func();
}


} // namespace medida