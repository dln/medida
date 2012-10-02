//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/stats/snapshot.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace medida {
namespace stats {

Snapshot::Snapshot(const std::vector<double>& values)
    : values_ {values} {
  std::sort(std::begin(this->values_), std::end(this->values_));
}


Snapshot::~Snapshot() {
}


std::size_t Snapshot::size() const {
 return values_.size();
}


std::vector<double> Snapshot::getValues() const {
  return values_;
}


double Snapshot::getValue(double quantile) const {
  if (quantile < 0.0 || quantile > 1.0) {
    throw std::invalid_argument("quantile is not in [0..1]");
  }

  if (values_.empty()) {
    return 0.0;
  }

  auto pos = quantile * (values_.size() + 1);

  if (pos < 1) {
    return values_.front();
  }

  if (pos >= values_.size()) {
    return values_.back();
  }

  auto lower = values_[pos - 1];
  auto upper = values_[pos];
  return lower + (pos - std::floor(pos)) * (upper - lower);
}


double Snapshot::getMedian() const {
  return getValue(kMEDIAN_Q);
}


double Snapshot::get75thPercentile() const {
  return getValue(kP75_Q);
}


double Snapshot::get95thPercentile() const {
  return getValue(kP95_Q);
}


double Snapshot::get98thPercentile() const {
  return getValue(kP98_Q);
}


double Snapshot::get99thPercentile() const {
  return getValue(kP99_Q);
}


double Snapshot::get999thPercentile() const {
  return getValue(kP999_Q);
}


// Explicit instantiations of template constructors


// template Snapshot::Snapshot<std::vector<std::atomic<std::int64_t>>::const_iterator>(
//     std::vector<std::atomic<std::int64_t>>::const_iterator,
//     std::vector<std::atomic<std::int64_t>>::const_iterator
// );


// template Snapshot::Snapshot<std::vector<std::int64_t>::const_iterator>(
//     std::vector<std::int64_t>::const_iterator,
//     std::vector<std::int64_t>::const_iterator
// );


// template Snapshot::Snapshot<std::vector<double>::const_iterator>(
//     std::vector<double>::const_iterator,
//     std::vector<double>::const_iterator
// );


// template Snapshot::Snapshot<std::vector<double>::iterator>(
//     std::vector<double>::iterator,
//     std::vector<double>::iterator
// );


// template Snapshot::Snapshot<double>(const std::map<double, std::int64_t>&);


} // namespace stats
} // namespace medida
