//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRICS_SNAPSHOT_H_
#define MEDIDA_METRICS_SNAPSHOT_H_

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace medida {

class Snapshot {
public:
  Snapshot();
  Snapshot(const std::vector<double>& values);
  Snapshot(const std::vector<std::int64_t>& values);
  Snapshot(const std::vector<std::atomic<std::int64_t>>& values);
  ~Snapshot();
  std::size_t size() const;
  double getValue(double quantile) const;
  double getMedian() const;
  double get75thPercentile() const;
  double get95thPercentile() const;
  double get98thPercentile() const;
  double get99thPercentile() const;
  double get999thPercentile() const;
  std::vector<double> getValues() const;
  // void dump(File output); 
protected:
  void Init();
  std::vector<double> values_;
  static constexpr double kMEDIAN_Q = 0.5;
  static constexpr double kP75_Q = 0.75;
  static constexpr double kP95_Q = 0.95;
  static constexpr double kP98_Q = 0.98;
  static constexpr double kP99_Q = 0.99;
  static constexpr double kP999_Q = 0.999;
};

}

#endif // MEDIDA_METRICS_SNAPSHOT_H_
