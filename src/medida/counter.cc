//
// Copyright (c) 2012 Daniel Lundin
//

#include <cstdatomic>
#include <cstddef>
#include <cstdint>

#include "medida/counter.h"

namespace medida {

  Counter::Counter() : count_ {0} {
    clear();
  }

  Counter::~Counter() {
  }

  void Counter::inc(std::int64_t n) {
    count_ += n;
  }

  void Counter::dec(std::int64_t n) {
    count_ -= n;
  }

  std::int64_t Counter::getCount() const {
    return count_.load();
  }

  void Counter::clear() {
    count_.store(0);
  }

  // void Counter::processWith(MetricProcessor<T> processor MetricName name, T context) {
  //   processor.processCounter(name, this, context);
  // }

}