//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_UNIFORM_SAMPLE_H_
#define MEDIDA_UNIFORM_SAMPLE_H_

#include <array>
#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <random>
#include <vector>

#include "medida/stats/sample.h"

namespace medida {
namespace stats {

class UniformSample : public Sample {
public:
  UniformSample(std::uint32_t reservoirSize);
  ~UniformSample();
  virtual void Clear();
  virtual std::uint64_t size() const;
  virtual void Update(std::int64_t value);
  virtual Snapshot MakeSnapshot() const;
protected:
    std::uint64_t reservoir_size_;
    std::atomic<std::uint64_t> count_;
    std::vector<std::atomic<std::int64_t>> values_;
    mutable std::mt19937_64 rng_;
    mutable std::mutex rng_mutex_;
};

} // namespace stats
} // namespace medida

#endif // MEDIDA_UNIFORM_SAMPLE_H_
