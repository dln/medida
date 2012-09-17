//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/meter.h"

#include "glog/logging.h"

namespace medida {

const Clock::duration::rep Meter::kTickInterval = std::chrono::duration_cast<Clock::duration>(std::chrono::seconds(5)).count();

Meter::Meter(std::string event_type, Clock::duration rate_unit) 
    : event_type_ {event_type},
      rate_unit_  {rate_unit},
      count_      {0},
      start_time_ {Clock::now()},
      last_tick_  {std::chrono::duration_cast<std::chrono::nanoseconds>(start_time_.time_since_epoch()).count()},
      m1_rate_    {stats::EWMA::oneMinuteEWMA()},
      m5_rate_    {stats::EWMA::fiveMinuteEWMA()},
      m15_rate_   {stats::EWMA::fifteenMinuteEWMA()} {
  DLOG(INFO) << "Meter " << this << " created. event_type=" << event_type << " rate_unit=" << rate_unit.count();
}

Meter::~Meter() {
  DLOG(INFO) << "Meter " << this << " destroyed";
}

std::chrono::nanoseconds Meter::rate_unit() const {
  return rate_unit_;
}

std::string Meter::event_type() const {
  return event_type_;
}

std::uint64_t Meter::count() const {
  return count_.load();
}

double Meter::fifteen_minute_rate() {
  TickIfNecessary();
  return m15_rate_.getRate();
}

double Meter::five_minute_rate() {
  TickIfNecessary();
  return m5_rate_.getRate();
}

double Meter::one_minute_rate() {
  TickIfNecessary();
  return m1_rate_.getRate();
}

double Meter::mean_rate() {
  auto c = count_.load();
  if (c > 0) {
    std::chrono::nanoseconds elapsed = Clock::now() - start_time_;
    return (c * rate_unit_.count()) / (double)elapsed.count();
  }
  return 0.0;
}

void Meter::Mark(std::uint64_t n) {
  TickIfNecessary();
  count_ += n;
  m1_rate_.update(n);
  m5_rate_.update(n);
  m15_rate_.update(n);
}

void Meter::Tick() {
  m1_rate_.tick();
  m5_rate_.tick();
  m15_rate_.tick();
}

void Meter::TickIfNecessary() {
  auto old_tick = last_tick_.load();
  auto new_tick = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now().time_since_epoch()).count();
  auto age = new_tick - old_tick;
  if (age > kTickInterval) {
    last_tick_ = new_tick;
    auto required_ticks = age / kTickInterval;
    for (auto i = 0; i < required_ticks; i ++) {
      Tick();
    }
  }
}

void Meter::Process(const MetricProcessor& processor) const  {
  DLOG(INFO) << "Processing Meter " << this;
  processor.Process(*this);
}


} // namespace medida