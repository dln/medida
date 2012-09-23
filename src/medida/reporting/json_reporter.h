//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_REPORTING_JSON_REPORTER_H_
#define MEDIDA_REPORTING_JSON_REPORTER_H_

#include <cstdint>
#include <iostream>
#include <mutex>
#include <ostream>
#include <string>
#include <sstream>

#include "medida/metric_processor.h"
#include "medida/reporting/abstract_reporter.h"

namespace medida {
namespace reporting {

class JsonReporter : public AbstractReporter, MetricProcessor {
public:
  JsonReporter(MetricsRegistry &registry);
  virtual ~JsonReporter();
  virtual void Process(Counter& counter);
  virtual void Process(Meter& meter);
  virtual void Process(Histogram& histogram);
  virtual void Process(Timer& timer);
  virtual std::string Report();
protected:
  std::string FormatRateUnit(const std::chrono::nanoseconds& rate_unit) const;
  mutable std::mutex mutex_;
  std::stringstream out_;
  std::string uname_;
};


} // namespace reporting
} // namespace medida

#endif // MEDIDA_REPORTING_JSON_REPORTER_H_
