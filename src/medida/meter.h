//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METER_H_
#define MEDIDA_METER_H_

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>

#include "medida/stats/ewma.h"
#include "medida/metered_interface.h"
#include "medida/metric_interface.h"
#include "medida/metric_processor.h"
#include "medida/stats/sample.h"

namespace medida {

class Meter : public MetricInterface, MeteredInterface {
public:
  Meter(std::string event_type, std::chrono::nanoseconds rate_unit = std::chrono::seconds(1));
  ~Meter();
  virtual std::chrono::nanoseconds rate_unit() const;
  virtual std::string event_type() const;
  virtual std::uint64_t count() const;
  virtual double fifteen_minute_rate();
  virtual double five_minute_rate();
  virtual double one_minute_rate();
  virtual double mean_rate();
  void Mark(std::uint64_t n = 1);
  void Process(const MetricProcessor& processor) const;
protected:
  static const Clock::duration::rep kTickInterval;
  const std::string event_type_;
  const std::chrono::nanoseconds rate_unit_;
  std::atomic<std::uint64_t> count_;
  const Clock::time_point start_time_;
  std::atomic<std::uint64_t> last_tick_;
  stats::EWMA m1_rate_;
  stats::EWMA m5_rate_;
  stats::EWMA m15_rate_;
  void Tick();
  void TickIfNecessary();
};

} // namespace medida

#endif // MEDIDA_METER_H_
