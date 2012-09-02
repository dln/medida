//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRICS_REGISTRY_H_
#define MEDIDA_METRICS_REGISTRY_H_

#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "medida/counter.h"
#include "medida/metric.h"
#include "medida/metric_name.h"

namespace medida {

class MetricsRegistry {
public:
  MetricsRegistry();
  ~MetricsRegistry();
  Counter& NewCounter(const MetricName &name, std::int64_t init_value = 0);
protected:
  std::map<MetricName, std::shared_ptr<Metric>> metrics_; // FIXME: gcc 4.4 doesn't work w/unique_ptr in maps
  mutable std::mutex mutex_;
};

} // namespace medida

#endif // MEDIDA_METRICS_REGISTRY_H_
