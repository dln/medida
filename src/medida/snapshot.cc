//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/snapshot.h"

namespace medida {

  Snapshot::Snapshot() {
  }

  Snapshot::~Snapshot() {
  }

  double getValue(double quantile);
  std::size_t size();
  double getMedian(); 
  double get75thPercentile();
  double get95thPercentile();
  double get98thPercentile();
  double get99thPercentile();
  double get999thPercentile();
  // double[] getValues();
  // void dump(File output); 
  static constexpr double kMEDIAN_Q = 0.5f;
  static constexpr double kP75_Q = 0.75f;
  static constexpr double kP95_Q = 0.95f;
  static constexpr double kP98_Q = 0.98f;
  static constexpr double kP99_Q = 0.99f;
  static constexpr double kP999_Q = 0.999f;

}