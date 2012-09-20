//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/reporting/abstract_reporter.h"

namespace medida {
namespace reporting {

AbstractReporter::AbstractReporter(MetricsRegistry &registry)
    // FIXME: GCC Bug 50025 - Uniform initialization of reference members broken
    : registry_ (registry) {
}


AbstractReporter::~AbstractReporter() {
}

void AbstractReporter::Shutdown() {
}


} // namespace reporting
} // namespace medida
