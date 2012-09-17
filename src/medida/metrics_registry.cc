//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/metrics_registry.h"

#include "glog/logging.h"

#include "medida/metric_name.h"

namespace medida {

  MetricsRegistry::MetricsRegistry() {
    DLOG(INFO) << "MetricsRegistry initialized.";
  }

  MetricsRegistry::~MetricsRegistry() {
    DLOG(INFO) << "MetricsRegistry destroyed.";
  }

Counter& MetricsRegistry::NewCounter(const MetricName &name, std::int64_t init_value) {
  std::lock_guard<std::mutex> lock {mutex_};
  if (metrics_.find(name) == std::end(metrics_)) {
    DLOG(INFO) << "NewCounter: " << name.ToString() << " does not exist. Creating.";
    metrics_[name].reset(new Counter(init_value)); // GCC 4.6: Bug 44436 emplace* not implemented
  } else {
    DLOG(INFO) << "NewCounter: " << name.ToString() << " already exists.";
  }
  return dynamic_cast<Counter&>(*metrics_[name]);
}

Histogram& MetricsRegistry::NewHistogram(const MetricName &name, SamplingInterface::SampleType sample_type) {
  std::lock_guard<std::mutex> lock {mutex_};
  if (metrics_.find(name) == std::end(metrics_)) {
    DLOG(INFO) << "NewHistogram: " << name.ToString() << " does not exist. Creating.";
    metrics_[name].reset(new Histogram(sample_type)); // GCC 4.6: Bug 44436 emplace* not implemented
  } else {
    DLOG(INFO) << "NewHistogram: " << name.ToString() << " already exists.";
  }
  return dynamic_cast<Histogram&>(*metrics_[name]);
}

} // namespace medida