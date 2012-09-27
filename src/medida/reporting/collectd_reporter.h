//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_REPORTING_COLLECTD_REPORTER_H_
#define MEDIDA_REPORTING_COLLECTD_REPORTER_H_

#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "medida/metric_name.h"
#include "medida/metric_processor.h"
#include "medida/reporting/abstract_polling_reporter.h"

namespace medida {
namespace reporting {

class CollectdReporter : public AbstractPollingReporter, MetricProcessor {
 public:
  CollectdReporter(MetricsRegistry &registry, const std::string& hostname = "127.0.0.1", std::uint16_t port = 25826);
  virtual ~CollectdReporter();
  virtual void Run();
  virtual void Process(Counter& counter);
  virtual void Process(Meter& meter);
  virtual void Process(Histogram& histogram);
  virtual void Process(Timer& timer);
 private:
  enum PartType {
    kHost =           0x0000,
    kTime =           0x0001,
    kPlugin =         0x0002,
    kPluginInstance = 0x0003,
    kType =           0x0004,
    kTypeInstance =   0x0005,
    kValues =         0x0006,
    kInterval =       0x0007,
    kMessage =        0x0100,
    kSeverity =       0x0101,
  };
  enum DataType {
    kCounter =  0x00,
    kGauge =    0x01,
    kDerive =   0x02,
    kAbsolute = 0x03,
  };
  struct Value {
    DataType type;
    double value;
  };
  static const int kMaxSize = 1024;
  std::string uname_;
  std::mutex mutex_;
  struct addrinfo *addrinfo_;
  int socket_;
  char msgbuf_[kMaxSize];
  char* msgbuf_ptr_;
  std::string current_instance_;
  void AddPart(PartType type, std::uint64_t number);
  void AddPart(PartType type, const std::string& text);
  void AddValues(std::initializer_list<Value> values);
  inline void pack8(std::uint8_t data);
  inline void pack16(std::uint16_t data);
  inline void pack64(std::uint64_t data);
  inline void pack_double(double data);
  inline void move_ptr(std::uint16_t offset);
};


} // namespace reporting
} // namespace medida

#endif // MEDIDA_REPORTING_COLLECTD_REPORTER_H_
