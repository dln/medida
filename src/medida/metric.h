//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRIC_H_
#define MEDIDA_METRIC_H_

#include "medida/metric_processor.h"

namespace medida {

class Metric {
public:
  virtual ~Metric() {};
  virtual void Process(const MetricProcessor& processor) const = 0;
};

} // namespace medida

#endif // MEDIDA_METRIC_H_
