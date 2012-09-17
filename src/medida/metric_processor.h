//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRIC_PROCESSOR_H_
#define MEDIDA_METRIC_PROCESSOR_H_

#include "medida/metric_interface.h"

namespace medida {

class MetricInterface;

class MetricProcessor {
public:
  virtual ~MetricProcessor() = 0;
  virtual void Process(const MetricInterface& metric) const = 0;
};

} // namespace medida

#endif // MEDIDA_METRIC_PROCESSOR_H_
