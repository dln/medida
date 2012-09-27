//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/reporting/collectd_reporter.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/utsname.h>

#include "medida/reporting/util.h"

namespace medida {
namespace reporting {

CollectdReporter::CollectdReporter(MetricsRegistry &registry, const std::string& hostname, std::uint16_t port)
    : AbstractPollingReporter(registry) {
  utsname name;
  uname_ = uname(&name) ? "localhost" : name.nodename;
  auto port_str = std::to_string(port);
  auto err = getaddrinfo(hostname.c_str(), port_str.c_str(), NULL, &addrinfo_);
  if (err != 0) {
    throw std::invalid_argument("getaddrinfo error: " + std::string(gai_strerror(err)));
  }
  socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (socket_ == -1) {
    std::stringstream ss;
    ss << "Socket error (" << errno << "): " << strerror(errno);
    throw std::runtime_error(ss.str());
  }
}


CollectdReporter::~CollectdReporter() {
  freeaddrinfo(addrinfo_);
}


void CollectdReporter::Run() {
  std::lock_guard<std::mutex> lock {mutex_};
  for (auto& kv : registry_.GetAllMetrics()) {
    auto name = kv.first;
    auto metric = kv.second;
    auto scope = name.scope();
    current_instance_ = name.name() + (scope.empty() ? "" : "." + scope);

    // Reset message
    msgbuf_ptr_ = &msgbuf_[0];

    // Add message parts
    AddPart(kTime, std::time(0));
    AddPart(kHost, uname_);
    AddPart(kPlugin, name.domain() + "." + name.type());
    metric->Process(*this);

    // Send message
    auto msg_size = msgbuf_ptr_ - msgbuf_;
    sendto(socket_, msgbuf_, msg_size, 0, addrinfo_->ai_addr, addrinfo_->ai_addrlen);
  }
}


void CollectdReporter::Process(Counter& counter) {
  double count = counter.count();
  AddPart(kType, "medida_counter");
  AddPart(kTypeInstance, current_instance_ + ".count");
  AddValues({{kGauge, count}});
}


void CollectdReporter::Process(Meter& meter) {
  auto event_type = meter.event_type();
  auto unit = FormatRateUnit(meter.rate_unit());
  double count = meter.count();
  AddPart(kType, "medida_meter");
  AddPart(kTypeInstance, current_instance_ + "." + event_type +"_per_" + unit);
  AddValues({
    {kGauge, count},
    {kGauge, meter.mean_rate()},
    {kGauge, meter.one_minute_rate()},
    {kGauge, meter.five_minute_rate()},
    {kGauge, meter.fifteen_minute_rate()},
  });
}


void CollectdReporter::Process(Histogram& histogram) {
  auto snapshot = histogram.GetSnapshot();
  AddPart(kType, "medida_histogram");
  AddPart(kTypeInstance, current_instance_);
  AddValues({
    {kGauge, histogram.min()},
    {kGauge, histogram.max()},
    {kGauge, histogram.mean()},
    {kGauge, histogram.std_dev()},
    {kGauge, snapshot.getMedian()},
    {kGauge, snapshot.get75thPercentile()},
    {kGauge, snapshot.get95thPercentile()},
    {kGauge, snapshot.get98thPercentile()},
    {kGauge, snapshot.get99thPercentile()},
    {kGauge, snapshot.get999thPercentile()},
  });
}


void CollectdReporter::Process(Timer& timer) {
  auto snapshot = timer.GetSnapshot();
  AddPart(kType, "medida_timer");
  AddPart(kTypeInstance, current_instance_ + "." + FormatRateUnit(timer.duration_unit()));
  AddValues({
    {kGauge, timer.min()},
    {kGauge, timer.max()},
    {kGauge, timer.mean()},
    {kGauge, timer.std_dev()},
    {kGauge, snapshot.getMedian()},
    {kGauge, snapshot.get75thPercentile()},
    {kGauge, snapshot.get95thPercentile()},
    {kGauge, snapshot.get98thPercentile()},
    {kGauge, snapshot.get99thPercentile()},
    {kGauge, snapshot.get999thPercentile()},
  });
}


void CollectdReporter::AddPart(PartType type, std::uint64_t number) {
  pack16(type);
  pack16(12);
  pack64(number);
}


void CollectdReporter::AddPart(PartType type, const std::string& text) {
  auto len = text.size() + 1;
  pack16(type);
  pack16(len + 4);
  memcpy(msgbuf_ptr_, text.c_str(), len);
  move_ptr(len);
}


void CollectdReporter::AddValues(std::initializer_list<Value> values) {
  auto count = values.size();
  pack16(PartType::kValues);
  pack16(6 + count * 9); // 48 bit header, 8 + 64 bits per value
  pack16(count);
  for (auto& v : values) {
    pack8(v.type);
  }
  for (auto& v : values) {
    if (v.type == DataType::kGauge) {
      pack_double(v.value);
    } else {
      pack64(v.value);
    }
  }
}


void CollectdReporter::pack8(std::uint8_t data) {
  *msgbuf_ptr_ = data;
  move_ptr(1);
}


void CollectdReporter::pack16(std::uint16_t data) {
  *(std::uint16_t*)msgbuf_ptr_ = htobe16(data);
  move_ptr(2);
}


void CollectdReporter::pack64(std::uint64_t data) {
  *(std::uint64_t*)msgbuf_ptr_ = htobe64(data);
  move_ptr(8);
}


void CollectdReporter::pack_double(double data) {
  // FIXME: Should break on bigendian archs. collectd expects little-endian doubles
  *(double*)msgbuf_ptr_ = data;
  move_ptr(8);
}


void CollectdReporter::move_ptr(std::uint16_t offs) {
  msgbuf_ptr_ += offs;
  if (msgbuf_ptr_ > msgbuf_ + kMaxSize) {
    throw std::runtime_error("Message buffer overflow");
  }
}


} // namespace reporting
} // namespace medida
