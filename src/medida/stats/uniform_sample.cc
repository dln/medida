//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/stats/uniform_sample.h"

#include <algorithm>
#include <random>

#include "medida/stats/snapshot.h"

namespace medida {
namespace stats {

UniformSample::UniformSample(std::uint32_t reservoirSize)
    : reservoir_size_ {reservoirSize},
      count_          {},
      values_         (reservoirSize), // FIXME: Explicit and non-uniform
      rng_            {std::random_device()()},
      rng_mutex_      {} {
  Clear();
}


UniformSample::~UniformSample() {
}


void UniformSample::Clear() {
  for (auto& v : values_) {
    v = 0;
  }
  count_ = 0;
}


std::uint64_t UniformSample::size() const {
  std::uint64_t size = values_.size();
  std::uint64_t count = count_.load();
  return std::min(count, size);
}


void UniformSample::Update(std::int64_t value) {
  auto count = ++count_;
  auto size = values_.size();
  if (count < size) {
    values_[count - 1] = value;
  } else {
    std::uniform_int_distribution<> uniform(0, count - 1);
    std::lock_guard<std::mutex> lock {rng_mutex_}; // FIXME: Thread-local RNG?
    auto rand = uniform(rng_);
    if (rand < size) {
      values_[rand] = value;
    }
  }
}


Snapshot UniformSample::MakeSnapshot() const {
  std::uint64_t size = values_.size();
  std::uint64_t count = count_.load();
  auto begin = std::begin(values_);
  return Snapshot {begin, begin + std::min(count, size)};
}


} // namespace stats
} // namespace medida
