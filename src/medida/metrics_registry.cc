//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/metrics_registry.h"

#include <cstdint>
#include <mutex>

#include "medida/metric_name.h"

namespace medida {

  MetricsRegistry::MetricsRegistry() {
  }

  MetricsRegistry::~MetricsRegistry() {
  }

Counter& MetricsRegistry::NewCounter(const MetricName &name, std::int64_t init_value) {
  std::lock_guard<std::mutex> lock {mutex_};
  auto it = counters_.find(name);
  if (it == counters_.end()) {
    counters_[name] = std::make_shared<Counter>(init_value);
  }
  return *counters_[name];
}

}