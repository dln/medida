//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_EXP_DECAY_SAMPLE_H_
#define MEDIDA_EXP_DECAY_SAMPLE_H_

#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <map>
#include <mutex>
#include <random>

#include "medida/types.h"
#include "medida/stats/sample.h"

namespace medida {
namespace stats {

class ExpDecaySample : public Sample {
public:
  ExpDecaySample(std::uint32_t reservoirSize, double alpha);
  ~ExpDecaySample();
  virtual void Clear();
  virtual std::uint64_t size() const;
  virtual void Update(std::int64_t value);
  virtual void Update(std::int64_t value, Clock::time_point timestamp);
  virtual Snapshot MakeSnapshot() const;
protected:
  static const Clock::duration kRESCALE_THRESHOLD;
  const double alpha_;
  const std::uint64_t reservoirSize_;
  Clock::time_point startTime_;
  Clock::time_point nextScaleTime_;

  std::atomic<std::uint64_t> count_;
  std::map<double, std::int64_t> values_;
  std::mutex values_mutex_;
  std::mutex read_mutex_;
  std::mutex write_mutex_;
  mutable std::mt19937 rng_;
  std::uniform_real_distribution<> dist_;
  void Rescale(const Clock::time_point& when);

};

} // namespace stats
} // namespace medida

#endif // MEDIDA_EXP_DECAY_SAMPLE_H_
