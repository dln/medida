//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/uniform_sample.h"
#include "medida/snapshot.h"

#include <cstdatomic>  // GCC 4.4
#include <cstdint>
#include <vector>
#include <algorithm>
#include <array>
#include <iostream>

namespace medida {

UniformSample::UniformSample(std::uint32_t reservoirSize)
    : size_ {reservoirSize},
      count_ {1},
      values_ {new std::atomic<std::int64_t>[reservoirSize]} {
  clear();
}

UniformSample::~UniformSample() {
  delete[] values_;
}

void UniformSample::clear() {
  for (auto i = 0; i < size_; ++i) {
    values_[i].store(0);
  }
  count_.store(1);
}

std::uint64_t UniformSample::size() const {
  auto c = count_.load();
  if (c > size_) {
    return size_;
  }
  return c;
}

void UniformSample::update(std::int64_t value) {
  auto c = count_++;
  if (c <= size_) {
    values_[c - 1].store(value);
  } else {
    auto r = nextLong(c);
    if (r < size_) {
      values_[r].store(value);
    }
  }
}

Snapshot UniformSample::getSnapshot() const {
  std::vector<std::int64_t> copy;
  copy.reserve(size_);
  for (auto i = 0; i < size_; ++i) {
    copy.push_back(values_[i].load());
  }
  return {copy};
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