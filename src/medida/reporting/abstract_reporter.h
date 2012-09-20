//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_REPORTING_ABSTRACT_REPORTER_H_
#define MEDIDA_REPORTING_ABSTRACT_REPORTER_H_

#include <cstdint>

#include "medida/metrics_registry.h"

namespace medida {
namespace reporting {

class AbstractReporter {
public:
  AbstractReporter(MetricsRegistry& registry);
  virtual ~AbstractReporter();
  virtual void Shutdown();
protected:
  medida::MetricsRegistry& registry_;
};

} // namespace reporting
} // namespace medida

#endif // MEDIDA_REPORTING_ABSTRACT_REPORTER_H_
