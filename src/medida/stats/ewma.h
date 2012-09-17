//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_EWMA_H_
#define MEDIDA_EWMA_H_

#include <atomic>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace medida {
namespace stats {

class EWMA {
public:
  EWMA() = delete;
  EWMA(double alpha, std::chrono::nanoseconds interval);
  EWMA(EWMA &&other);
  ~EWMA();
  static EWMA oneMinuteEWMA();
  static EWMA fiveMinuteEWMA();
  static EWMA fifteenMinuteEWMA();
  void update(std::int64_t n);
  void tick();
  double getRate(std::chrono::nanoseconds duration = std::chrono::seconds {1}) const;
protected:
  static constexpr int kINTERVAL = 5;
  static constexpr double kSECONDS_PER_MINUTE = 60.0;
  static constexpr int kONE_MINUTE = 1;
  static constexpr int kFIVE_MINUTES = 5;
  static constexpr int kFIFTEEN_MINUTES = 15;
  static constexpr double kM1_ALPHA = 1 - std::exp(-kINTERVAL / kSECONDS_PER_MINUTE / kONE_MINUTE);
  static constexpr double kM5_ALPHA = 1 - std::exp(-kINTERVAL / kSECONDS_PER_MINUTE / kFIVE_MINUTES);
  static constexpr double kM15_ALPHA = 1 - std::exp(-kINTERVAL / kSECONDS_PER_MINUTE / kFIFTEEN_MINUTES);
  volatile bool initialized_;
  volatile double rate_;
  std::atomic<std::int64_t> uncounted_;
  const double alpha_;
  const std::uint64_t interval_nanos_;
};

} // namespace stats
} // namespace medida

#endif // MEDIDA_EWMA_H_
