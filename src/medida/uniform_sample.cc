//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/uniform_sample.h"

#include <algorithm>

#include "medida/snapshot.h"

namespace medida {

UniformSample::UniformSample(std::uint32_t reservoirSize)
    : count_  {1},
      values_ (reservoirSize) { // FIXME: Explicit and non-uniform
  clear();
}

UniformSample::~UniformSample() {
}

void UniformSample::clear() {
  for (auto& v : values_) {
    v.store(0);
  }
  count_.store(1);
}

std::uint64_t UniformSample::size() const {
  std::uint64_t size = values_.size();
  return std::min(count_.load(), size);
}

void UniformSample::update(std::int64_t value) {
  auto c = count_.fetch_add(1);
  auto size = values_.size();
  if (c <= size) {
    values_[c - 1].store(value);
  } else {
    auto r = nextLong(c);
    if (r < size) {
      values_[r].store(value);
    }
  }
}

Snapshot UniformSample::getSnapshot() const {
  return {values_};
}

std::int64_t UniformSample::nextLong(std::int64_t n) const {
  std::uint64_t bits, val;
  do {
    // FIXME: replace std::rand with boost::random::mt19937_64
    bits = std::rand() & (~(1L << kBITS_PER_LONG));
    val = bits % n;
  } while (bits - val + (n - 1) < 0L);
  return val;
}

}