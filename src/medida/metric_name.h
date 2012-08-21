//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRIC_NAME_H_
#define MEDIDA_METRIC_NAME_H_

#include <cstddef>
#include <string>

namespace medida {

class MetricName {
public:
  MetricName(const std::string &domain, const std::string &type, const std::string &name, const std::string &scope = "");
  ~MetricName();
  std::string domain() const;
  std::string type() const;
  std::string name() const;
  std::string scope() const;
  std::string ToString() const;
  bool has_scope() const;
  bool operator==(const MetricName& other) const;
  bool operator!=(const MetricName& other) const;

protected:
    const std::string domain_;
    const std::string type_;
    const std::string name_;
    const std::string scope_;
};


} // namespace medida

#endif // MEDIDA_METRIC_NAME_H_
