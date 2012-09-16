//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_HISTOGRAM_H_
#define MEDIDA_HISTOGRAM_H_

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>

#include "medida/metric.h"
#include "medida/stats/sample.h"
#include "medida/stats/snapshot.h"

namespace medida {

class Histogram : public Metric {
public:
  enum SampleType { kUniform, kBiased };
  Histogram(SampleType sample_type = SampleType::kUniform);
  ~Histogram();
  void Update(std::int64_t value);
  std::uint64_t count() const;
  double sum() const;
  double max() const;
  double min() const;
  double mean() const;
  double std_dev() const;
  double variance() const;
  stats::Snapshot GetSnapshot() const;
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
