//
// Copyright (c) 2012 Daniel Lundin
//

#include <cstdatomic>
#include <cstddef>
#include <cstdint>

#include "medida/metric_name.h"

namespace medida {

  MetricName::MetricName(std::string group, std::string type, std::string name, std::string scope, std::string bean)
      : group_(group),
        type_(type),
        name_(name),
        scope_(scope),
        bean_(bean) {
  }

  MetricName::~MetricName() {

  }

  std::string MetricName::getGroup() const {
    return group_;
  }

  std::string MetricName::getType() const {
    return type_;
  }

  std::string MetricName::getName() const {
    return name_;
  }

  std::string MetricName::getScope() const {
    return scope_;
  }

  std::string MetricName::getBean() const {
    return bean_;
  }

  std::string MetricName::toString() const {
    return bean_;
  }

  bool MetricName::hasScope() const {
    return scope_.empty();
  }

  bool MetricName::equals(const MetricName &other) const {
    return false;
  }

  int MetricName::compareTo(const MetricName &other) const {
    return 0;
  }

}