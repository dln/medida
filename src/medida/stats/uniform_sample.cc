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
    : count_  {1},
      random_ {std::random_device()()},
      values_ (reservoirSize) { // FIXME: Explicit and non-uniform
  clear();
}

UniformSample::~UniformSample() {
}

void UniformSample::clear() {
  for (auto& v : values_) {
    v = 0;
  }
  count_ = 1;
}

std::uint64_t UniformSample::size() const {
  std::uint64_t size = values_.size();
  return std::min(count_.load(), size);
}

void UniformSample::update(std::int64_t value) {
  auto c = count_++;
  auto size = values_.size();
  if (c <= size) {
    values_[c - 1] = value;
  } else {
    auto r = nextLong(c);
    if (r < size) {
      values_[r] = value;
    }
  }
}

Snapshot UniformSample::getSnapshot() const {
  return {values_};
}

std::int64_t UniformSample::nextLong(std::int64_t n) const {
  // FIXME: Thread-local RNG would be nice.
  std::lock_guard<std::mutex> lock {random_mutex_};
  std::uint64_t bits, val;
  do {
    bits = random_();
    val = bits % n;
  } while (bits - val + (n - 1) < 0L);
  return val;
}

} // namespace stats
} // namespace medida
