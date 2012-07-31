//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRICS_SNAPSHOT_H_
#define MEDIDA_METRICS_SNAPSHOT_H_

#include <cstddef>
#include <vector>

namespace medida {

class Snapshot {
public:
  Snapshot();
  Snapshot(std::vector<double> values);
  // Snapshot(Collection<Long> values) {
  ~Snapshot();
  std::size_t size() const { return values.size(); };
  double getValue(double quantile) const;
  double getMedian() const { return getValue(kMEDIAN_Q); };
  double get75thPercentile() const { return getValue(kP75_Q); };
  double get95thPercentile() const { return getValue(kP95_Q); };
  double get98thPercentile() const { return getValue(kP98_Q); };
  double get99thPercentile() const { return getValue(kP99_Q); };
  double get999thPercentile() const { return getValue(kP999_Q); };

  std::vector<double> getValues() const;

  // void dump(File output); 
  static constexpr double kMEDIAN_Q = 0.5f;
  static constexpr double kP75_Q = 0.75f;
  static constexpr double kP95_Q = 0.95f;
  static constexpr double kP98_Q = 0.98f;
  static constexpr double kP99_Q = 0.99f;
  static constexpr double kP999_Q = 0.999f;

protected:
  std::vector<double> values;

};

}

#endif // MEDIDA_METRICS_SNAPSHOT_H_
