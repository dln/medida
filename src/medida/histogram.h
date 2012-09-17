//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_HISTOGRAM_H_
#define MEDIDA_HISTOGRAM_H_

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>

#include "medida/metric_interface.h"
#include "medida/sampling_interface.h"
#include "medida/summarizable_interface.h"
#include "medida/stats/sample.h"

namespace medida {

class Histogram : public MetricInterface, SamplingInterface, SummarizableInterface {
public:
  Histogram(SampleType sample_type = kUniform);
  ~Histogram();
  virtual stats::Snapshot GetSnapshot() const;
  virtual double sum() const;
  virtual double max() const;
  virtual double min() const;
  virtual double mean() const;
  virtual double std_dev() const;
  void Update(std::int64_t value);
  std::uint64_t count() const;
  double variance() const;
  void Process(const MetricProcessor& processor) const;
  void Clear();
protected:
  static const std::uint64_t kDefaultSampleSize = 1028;
  static const std::uint64_t kDefaultAlpha = 0.015;
  std::unique_ptr<stats::Sample> sample_;
  std::atomic<std::int64_t> min_;
  std::atomic<std::int64_t> max_;
  std::atomic<std::int64_t> sum_;
  std::atomic<std::uint64_t> count_;
  double variance_m_;
  double variance_s_;
  mutable std::mutex variance_mutex_;
};

} // namespace medida

#endif // MEDIDA_HISTOGRAM_H_
