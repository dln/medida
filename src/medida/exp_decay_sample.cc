//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/exp_decay_sample.h"

#include <cmath>

#include "medida/snapshot.h"

namespace medida {

const Clock::duration ExpDecaySample::kRESCALE_THRESHOLD = std::chrono::hours{1};

ExpDecaySample::ExpDecaySample(std::uint32_t reservoirSize, double alpha)
    : alpha_         {alpha},
      reservoirSize_ {reservoirSize},
      count_         {1} {
  clear();
}

ExpDecaySample::~ExpDecaySample() {
}

void ExpDecaySample::clear() {
  std::lock_guard<std::mutex> lock {write_mutex_};
  values_.clear();
  count_ = 1;
  startTime_ = Clock::now();
  nextScaleTime_ = startTime_ + kRESCALE_THRESHOLD;
}

std::uint64_t ExpDecaySample::size() const {
  return std::min(reservoirSize_, count_.load());
}

void ExpDecaySample::update(std::int64_t value) {
  update(value, Clock::now());
}

void ExpDecaySample::update(std::int64_t value, Clock::time_point timestamp) {
  {
    std::lock_guard<std::mutex> lock {read_mutex_};
    auto priority = weight(timestamp - startTime_) / (std::rand() / RAND_MAX);
    auto newCount = count_++;
    auto first = std::begin(values_)->first;
    if (first < priority) {
      if (values_.insert({priority, value}).second) {
        while (values_.erase(first) == 0) {
          first = std::begin(values_)->first;
        }
      }
    }
  }

  auto now = Clock::now();
  if (now >= nextScaleTime_) {
    // rescale(now);
  }



  /*
            final double priority = weight(timestamp - startTime) / ThreadLocalRandom.current().nextDouble();
            final long newCount = count.incrementAndGet();
            if (newCount <= reservoirSize) {
                values.put(priority, value);
            } else {
                Double first = values.firstKey();
                if (first < priority) {
                    if (values.putIfAbsent(priority, value) == null) {
                        // ensure we always remove an item
                        while (values.remove(first) == null) {
                            first = values.firstKey();
                        }
                    }
                }
            }

        final long now = System.nanoTime();
        final long next = nextScaleTime.get();
        if (now >= next) {
            rescale(now, next);
        }
    */
}

double ExpDecaySample::weight(Clock::duration dur) const {
  return std::exp(alpha_ * dur.count());
}


Snapshot ExpDecaySample::getSnapshot() const {

}

} // namespace medida