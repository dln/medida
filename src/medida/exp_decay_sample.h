//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_EXP_DECAY_SAMPLE_H_
#define MEDIDA_EXP_DECAY_SAMPLE_H_

#include <array>
#include <atomic>
#include <chrono>
#include <map>
#include <mutex>
#include <cstdint>

#include "medida/sample.h"
#include "medida/types.h"

namespace medida {

class ExpDecaySample : public Sample {
public:
  ExpDecaySample(std::uint32_t reservoirSize, double alpha);
  ~ExpDecaySample();
  virtual void clear();
  virtual std::uint64_t size() const;
  virtual void update(std::int64_t value);
  virtual void update(std::int64_t value, Clock::time_point timestamp);
  virtual Snapshot getSnapshot() const;
protected:
  static const Clock::duration kRESCALE_THRESHOLD;
  const double alpha_;
  const std::uint64_t reservoirSize_;
  Clock::time_point startTime_;
  Clock::time_point nextScaleTime_;

  std::atomic<std::uint64_t> count_;
  std::map<double, int64_t> values_;
  std::mutex values_mutex_;
  std::mutex read_mutex_;
  std::mutex write_mutex_;
  double weight(Clock::duration dur) const;
  void rescale(long now, long next);

};

} // namespace medida

#endif // MEDIDA_EXP_DECAY_SAMPLE_H_
