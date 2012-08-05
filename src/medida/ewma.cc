//
// Copyright (c) 2012 Daniel Lundin
//

#include <cmath>

#include "medida/ewma.h"

namespace medida {

  // GCC 4.4 doesn't support constexpr
  const double EWMA::kM1_ALPHA = 1 - std::exp(-kINTERVAL / kSECONDS_PER_MINUTE / kONE_MINUTE);
  const double EWMA::kM5_ALPHA = 1 - std::exp(-kINTERVAL / kSECONDS_PER_MINUTE / kFIVE_MINUTES);
  const double EWMA::kM15_ALPHA = 1 - std::exp(-kINTERVAL / kSECONDS_PER_MINUTE / kFIFTEEN_MINUTES);

  EWMA::EWMA(double alpha, std::chrono::nanoseconds interval)
      : initialized_ {false},
        rate_ {0.0},
        uncounted_ {0},
        alpha_ {alpha},
        interval_ {interval} {
  }

  EWMA::EWMA(EWMA &&other) 
      : initialized_ {other.initialized_},
        rate_ {other.rate_},
        uncounted_ {other.uncounted_.load()},
        alpha_ {other.alpha_},
        interval_ {other.interval_} {
  }

  EWMA::~EWMA() {
  }

  EWMA EWMA::oneMinuteEWMA() {
    return {kM1_ALPHA, std::chrono::seconds{5}};
  }

  EWMA EWMA::fiveMinuteEWMA() {
    return {kM5_ALPHA, std::chrono::seconds{5}};
  }

  EWMA EWMA::fifteenMinuteEWMA() {
    return {kM15_ALPHA, std::chrono::seconds{5}};
  }

  void EWMA::update(std::int64_t n) {
    uncounted_ += n;
  }

  void EWMA::tick() {
    double count = uncounted_.exchange(0);
    auto instantRate = count / interval_.count();
    if (initialized_) {
      rate_ += (alpha_ * (instantRate - rate_));
    } else {
      rate_ = instantRate;
      initialized_ = true;
    }
  }

  double EWMA::getRate(std::chrono::nanoseconds duration) const {
    return rate_ * duration.count();
  }
}