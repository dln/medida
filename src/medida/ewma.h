//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_EWMA_H_
#define MEDIDA_EWMA_H_

#include <chrono>
#include <cstdatomic>
#include <cstddef>
#include <cstdint>

namespace medida {

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
  static const int kINTERVAL = 5;
  static const double kSECONDS_PER_MINUTE = 60.0;
  static const int kONE_MINUTE = 1;
  static const int kFIVE_MINUTES = 5;
  static const int kFIFTEEN_MINUTES = 15;
  static const double kM1_ALPHA;
  static const double kM5_ALPHA;
  static const double kM15_ALPHA;
  volatile bool initialized_;
  volatile double rate_;
  std::atomic<std::int64_t> uncounted_;
  const double alpha_;
  const std::chrono::nanoseconds interval_;
};

} // namespace medida

#endif // MEDIDA_EWMA_H_
