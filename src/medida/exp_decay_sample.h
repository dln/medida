//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_EXP_DECAY_SAMPLE_H_
#define MEDIDA_EXP_DECAY_SAMPLE_H_

#include <array>
#include <chrono>
#include <map>
#include <mutex>
#include <cstdatomic>  // GCC 4.4
#include <cstdint>

#include "medida/sample.h"

namespace medida {

class ExpDecaySample : public Sample {
public:
  ExpDecaySample(std::uint32_t reservoirSize, double alpha);
  ~ExpDecaySample();
  virtual void clear();
  virtual std::uint64_t size() const;
  virtual void update(std::int64_t value);
  virtual void update(std::int64_t value, std::chrono::high_resolution_clock::time_point timestamp);
  virtual Snapshot getSnapshot() const;
protected:
    static const std::chrono::nanoseconds kRESCALE_THRESHOLD; // = 3600L * 1000 * 1000 * 1000; // 1h in nanos
    const double alpha_;
    const std::uint64_t reservoirSize_;
    std::chrono::high_resolution_clock::time_point startTime_;
    std::atomic<std::uint64_t> nextScaleTime_;
    std::atomic<std::uint64_t> count_;
    std::map<double, uint64_t> values_;
    std::mutex values_mutex_;
    std::mutex read_mutex_;
    std::mutex write_mutex_;
    double weight() const;
    void rescale(long now, long next);

};

} // namespace medida

#endif // MEDIDA_EXP_DECAY_SAMPLE_H_
