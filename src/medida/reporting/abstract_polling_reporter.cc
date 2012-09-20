//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/reporting/abstract_polling_reporter.h"

#include <iostream>

namespace medida {
namespace reporting {

AbstractPollingReporter::AbstractPollingReporter(MetricsRegistry &registry)
    : AbstractReporter(registry),
      running_ {false},
      thread_ {} {
}


AbstractPollingReporter::~AbstractPollingReporter() {
  Shutdown();
}


void AbstractPollingReporter::Shutdown() {
  if (running_) {
    running_ = false;
    thread_.join();
  }
}


void AbstractPollingReporter::Loop(Clock::duration period) {
  while (running_) {
    std::this_thread::sleep_for(period);
    Run();
  }
}

void AbstractPollingReporter::Start(Clock::duration period) {
  if (!running_) {
    running_ = true;
    thread_ = std::thread(&AbstractPollingReporter::Loop, this, period);
  }
}


void AbstractPollingReporter::Run() {
}


} // namespace reporting
} // namespace medida
