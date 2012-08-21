//
// Copyright (c) 2012 Daniel Lundin
//

#include <cstdatomic>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "medida/metric_name.h"

namespace medida {

MetricName::MetricName(const std::string &domain, const std::string &type,
    const std::string &name, const std::string &scope)
    : domain_(domain),
      type_(type),
      name_(name),
      scope_(scope) {
  if (domain.empty()) {
    throw std::invalid_argument("domain must be non-empty");
  }
  if (type.empty()) {
    throw std::invalid_argument("type must be non-empty");
  }
  if (name.empty()) {
    throw std::invalid_argument("name must be non-empty");
  }
}

MetricName::~MetricName() {

}

std::string MetricName::domain() const {
  return domain_;
}

std::string MetricName::type() const {
  return type_;
}

std::string MetricName::name() const {
  return name_;
}

std::string MetricName::scope() const {
  return scope_;
}

std::string MetricName::ToString() const {
  return domain_ + "." + type_ + "." + name_  + (scope_.empty() ? "" : "." + scope_);
}

bool MetricName::has_scope() const {
  return !scope_.empty();
}

bool MetricName::operator==(const MetricName &other) const {
  return (
      domain_ == other.domain_ &&
      type_ == other.type_ &&
      name_ == other.name_ &&
      scope_ == other.scope_);
}

bool MetricName::operator!=(const MetricName &other) const {
  return (
      domain_ != other.domain_ ||
      type_ != other.type_ ||
      name_ != other.name_ ||
      scope_ != other.scope_);
}

} // name space medida
