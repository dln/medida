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
#include "medida/histogram.h"
#include "medida/metric_interface.h"
#include "medida/metric_name.h"

namespace medida {

class MetricsRegistry {
public:
  MetricsRegistry();
  ~MetricsRegistry();
  Counter& NewCounter(const MetricName &name, std::int64_t init_value = 0);
  Histogram& NewHistogram(const MetricName &name, SamplingInterface::SampleType sample_type = SamplingInterface::kUniform);
protected:
  std::map<MetricName, std::unique_ptr<MetricInterface>> metrics_;
  mutable std::mutex mutex_;
};

} // namespace medida

#endif // MEDIDA_METRICS_REGISTRY_H_
