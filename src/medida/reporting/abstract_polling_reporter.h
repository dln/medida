//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_REPORTING_ABSTRACT_POLLING_REPORTER_H_
#define MEDIDA_REPORTING_ABSTRACT_POLLING_REPORTER_H_

#include <atomic>
#include <thread>

#include "medida/reporting/abstract_reporter.h"
#include "medida/types.h"

namespace medida {
namespace reporting {

class AbstractPollingReporter : public AbstractReporter {
public:
  AbstractPollingReporter(MetricsRegistry& registry);
  virtual ~AbstractPollingReporter();
  virtual void Shutdown();
  virtual void Start(Clock::duration period);
  virtual void Run();
protected:
  std::atomic<bool> running_;
  std::thread thread_;
  void Loop(Clock::duration period);
};

} // namespace reporting
} // namespace medida

#endif // MEDIDA_REPORTING_ABSTRACT_POLLING_REPORTER_H_
