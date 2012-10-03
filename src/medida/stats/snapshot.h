//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRICS_SNAPSHOT_H_
#define MEDIDA_METRICS_SNAPSHOT_H_

#include <memory>
#include <vector>

namespace medida {
namespace stats {

class Snapshot {
 public:
  Snapshot(const std::vector<double>& values);
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
 private:
  class Impl;
  Impl* impl_;
  // std::unique_ptr<Impl> impl_;  // FIXME: y u incomplete type?!?
};


} // namespace stats
} // namespace medida

#endif // MEDIDA_METRICS_SNAPSHOT_H_
