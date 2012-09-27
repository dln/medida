//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/reporting/json_reporter.h"

#include <chrono>
#include <ctime>
#include <sys/utsname.h>

#include "medida/reporting/util.h"

namespace medida {
namespace reporting {

JsonReporter::JsonReporter(MetricsRegistry &registry)
    : AbstractReporter(registry),
      out_ {} {
  utsname name;
  uname_ = {uname(&name) ? "localhost" : name.nodename};
}


JsonReporter::~JsonReporter() {
}


std::string JsonReporter::Report() {
  auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(Clock::now().time_since_epoch()).count();
  auto t = std::time(NULL);
  char mbstr[32] = "";
  std::strftime(mbstr, 32, "%FT%T%z", std::localtime(&t));
  std::lock_guard<std::mutex> lock {mutex_};
  out_.str("");
  out_.clear();
  out_ << "{" << std::endl
       << "\"ts\":\"" << mbstr << "\"," << std::endl
       << "\"uname\":\"" << uname_ << "\"," << std::endl
       << "\"metrics\":{" << std::endl;
  auto first = true;
  for (auto& kv : registry_.GetAllMetrics()) {
    auto name = kv.first;
    auto metric = kv.second;
    if (first) {
      first = false;
    } else {
      out_ << ",";
    }
    out_ << "\"" << name.ToString() << "\":{" << std::endl;
    metric->Process(*this);
    out_ << "}" << std::endl;
  }
  out_ << "}"    // metrics
       << "}";  // top
  return out_.str();
}


void JsonReporter::Process(Counter& counter) {
  out_ << "\"type\":\"counter\"," << std::endl;
  out_ << "\"count\":" << counter.count() << std::endl;
}


void JsonReporter::Process(Meter& meter) {
  auto event_type = meter.event_type();
  auto unit = FormatRateUnit(meter.rate_unit());
  out_ << "\"type\":\"meter\"," << std::endl
       << "\"count\":" << meter.count() << "," << std::endl
       << "\"event_type\":\"" << event_type << "\"," << std::endl
       << "\"rate_unit\":\"" << unit << "\"," << std::endl
       << "\"mean_rate\":" << meter.mean_rate() << "," << std::endl
       << "\"1_min_rate\":" << meter.one_minute_rate() << "," << std::endl
       << "\"5_min_rate\":" << meter.five_minute_rate() << "," << std::endl
       << "\"15_min_rate\":" << meter.fifteen_minute_rate() << std::endl;
}


void JsonReporter::Process(Histogram& histogram) {
  auto snapshot = histogram.GetSnapshot();
  out_ << "\"type\":\"histogram\"," << std::endl
       << "\"min\":" << histogram.min() << "," << std::endl
       << "\"max\":" << histogram.max() << "," << std::endl
       << "\"mean\":" << histogram.mean() << "," << std::endl
       << "\"stddev\":" << histogram.std_dev() << "," << std::endl
       << "\"median\":" << snapshot.getMedian() << "," << std::endl
       << "\"75%\":" << snapshot.get75thPercentile() << "," << std::endl
       << "\"95%\":" << snapshot.get95thPercentile() << "," << std::endl
       << "\"98%\":" << snapshot.get98thPercentile() << "," << std::endl
       << "\"99%\":" << snapshot.get99thPercentile() << "," << std::endl
       << "\"99.9%\":" << snapshot.get999thPercentile() << std::endl;
}


void JsonReporter::Process(Timer& timer) {
  auto snapshot = timer.GetSnapshot();
  auto unit = FormatRateUnit(timer.duration_unit());
  out_ << "\"type\":\"timer\"," << std::endl
       << "\"unit\":\"" << unit << "\"," << std::endl
       << "\"min\":" << timer.min() << "," << std::endl
       << "\"max\":" << timer.max() << "," << std::endl
       << "\"mean\":" << timer.mean() << "," << std::endl
       << "\"stddev\":" << timer.std_dev() << "," << std::endl
       << "\"median\":" << snapshot.getMedian() << "," << std::endl
       << "\"75%\":" << snapshot.get75thPercentile() << "," << std::endl
       << "\"95%\":" << snapshot.get95thPercentile() << "," << std::endl
       << "\"98%\":" << snapshot.get98thPercentile() << "," << std::endl
       << "\"99%\":" << snapshot.get99thPercentile() << "," << std::endl
       << "\"99.9%\":" << snapshot.get999thPercentile() << std::endl;
}


} // namespace reporting
} // namespace medida
