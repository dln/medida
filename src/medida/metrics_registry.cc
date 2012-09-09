//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/metrics_registry.h"

#include <cstdint>
#include <mutex>

#include "medida/metric_name.h"

#include "glog/logging.h"

namespace medida {

  MetricsRegistry::MetricsRegistry() {
    DLOG(INFO) << "MetricsRegistry initialized.";
  }

  MetricsRegistry::~MetricsRegistry() {
    DLOG(INFO) << "MetricsRegistry destroyed.";
  }

Counter& MetricsRegistry::NewCounter(const MetricName &name, std::int64_t init_value) {
  std::lock_guard<std::mutex> lock {mutex_};
  auto it = metrics_.find(name);
  if (it == std::end(metrics_)) {
    DLOG(INFO) << "NewCounter: " << name.ToString() << " does not exist. Creating.";
    metrics_[name].reset(new Counter(init_value)); // GCC 4.6: Bug 44436 emplace* not implemented
  } else {
    DLOG(INFO) << "NewCounter: " << name.ToString() << " already exists.";
  }
  return dynamic_cast<Counter&>(*metrics_[name]);
}

}