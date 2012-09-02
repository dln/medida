//
// Copyright (c) 2012 Daniel Lundin
//

#include <cstdatomic>
#include <cstddef>
#include <cstdint>

#include "medida/counter.h"

namespace medida {

Counter::Counter(std::int64_t init) : count_ {init} {
}

Counter::~Counter() {
}

std::int64_t Counter::count() const {
  return count_.load();
}

void Counter::set_count(std::int64_t n) {
  count_.store(n);
}

void Counter::inc(std::int64_t n) {
  count_ += n;
}

void Counter::dec(std::int64_t n) {
  count_ -= n;
}

void Counter::clear() {
  set_count(0);
}

} // namespace medida