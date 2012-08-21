//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRIC_H_
#define MEDIDA_METRIC_H_

#include <chrono>


namespace medida {

class Metric {
public:
  Metric();
  ~Metric();

    // <T> void processWith(MetricProcessor<T> processor, MetricName name, T context) throws Exception;
  // virtual void processWith(MetricProcessor processor, MetricName name, T context);
};

} // namespace medida

#endif // MEDIDA_METRIC_H_
