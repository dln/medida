//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/snapshot.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

namespace medida {

  Snapshot::Snapshot() {
  }

  Snapshot::Snapshot(std::vector<double> values) : values(values) {
    std::sort(this->values.begin(), this->values.end());
  }

  Snapshot::Snapshot(std::vector<long> values) : values(values.begin(), values.end()) {
    std::sort(this->values.begin(), this->values.end());
  }

  Snapshot::~Snapshot() {
  }

  std::size_t Snapshot::size() const {
   return values.size();
  }

  std::vector<double> Snapshot::getValues() const {
    return values;
  }

  double Snapshot::getValue(double quantile) const {
    if (quantile < 0.0 || quantile > 1.0) {
      throw std::invalid_argument("quantile is not in [0..1]");
    }

    if (values.empty()) {
      return 0.0;
    }

    const double pos = quantile * (values.size() + 1);

    if (pos < 1) {
      return values.front();
    }

    if (pos >= values.size()) {
      return values.back();
    }

    const double lower = values.at(pos - 1);
    const double upper = values.at(pos);
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

}