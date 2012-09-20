//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/metrics_registry.h"

#include <algorithm>
#include <thread>

#include "medida/metric_name.h"

namespace medida {

MetricsRegistry::MetricsRegistry() {
}


MetricsRegistry::~MetricsRegistry() {
}


Counter& MetricsRegistry::NewCounter(const MetricName &name, std::int64_t init_value) {
  return NewMetric<Counter>(name, init_value);
}


Histogram& MetricsRegistry::NewHistogram(const MetricName &name,
    SamplingInterface::SampleType sample_type) {
  return NewMetric<Histogram>(name, sample_type);
}


Meter& MetricsRegistry::NewMeter(const MetricName &name, std::string event_type,
    Clock::duration rate_unit) {
  return NewMetric<Meter>(name, event_type, rate_unit);
}


Timer& MetricsRegistry::NewTimer(const MetricName &name, std::chrono::nanoseconds duration_unit,
    std::chrono::nanoseconds rate_unit) {
  return NewMetric<Timer>(name, duration_unit, rate_unit);
}


template<typename MetricType, typename... Args>
MetricType& MetricsRegistry::NewMetric(const MetricName& name, Args... args) {
  std::lock_guard<std::mutex> lock {mutex_};
  if (metrics_.find(name) == std::end(metrics_)) {
    // GCC 4.6: Bug 44436 emplace* not implemented. Use ::reset instead.
    // metrics_[name].reset(new MetricType(args...));
    metrics_[name] = std::make_shared<MetricType>(args...);
  } else {
  }
  return dynamic_cast<MetricType&>(*metrics_[name]);
}

std::map<MetricName, std::shared_ptr<MetricInterface>> MetricsRegistry::GetAllMetrics() const {
 return {metrics_}; 
}

void MetricsRegistry::ProcessAll(MetricProcessor& processor) {
  std::lock_guard<std::mutex> lock (mutex_);
  // std::this_thread::sleep_for(std::chrono::milliseconds(10));
  // auto it = std::begin(metrics_);
  // auto end = std::end(metrics_);
  // for (auto it = std::begin(metrics_); it != std::end(metrics_); it++ ) {
  // }
}


} // namespace medida