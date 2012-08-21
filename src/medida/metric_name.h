//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRIC_NAME_H_
#define MEDIDA_METRIC_NAME_H_

#include <cstdatomic>
#include <cstddef>
#include <cstdint>
#include <string>

namespace medida {

class MetricName {
public:
  MetricName(std::string group = "", std::string type = "", std::string name = "", 
      std::string scope = "", std::string bean = "");
  ~MetricName();
  std::string getGroup() const;
  std::string getType() const;
  std::string getName() const;
  std::string getScope() const;
  std::string getBean() const;
  std::string toString() const;
  bool hasScope() const;
  bool equals(const MetricName &other) const;
  int compareTo(const MetricName &other) const;
  //int hashCode() const;

protected:
    const std::string group_;
    const std::string type_;
    const std::string name_;
    const std::string scope_;
    const std::string bean_;
    static std::string createBean(
        const std::string &group, const std::string &type,
        const std::string &name, const std::string &scope);
};

/*
    public MetricName(Class<?> klass, String name) {
        this(klass, name, null);
    }

    public MetricName(String group, String type, String name) {
        this(group, type, name, null);
    }

    public MetricName(Class<?> klass, String name, String scope) {
        this(klass.getPackage() == null ? "" : klass.getPackage().getName(),
             klass.getSimpleName().replaceAll("\\$$", ""),
             name,
             scope);
    }

    public MetricName(String group, String type, String name, String scope) {
        this(group, type, name, scope, createMBeanName(group, type, name, scope));
    }

    public MetricName(String group, String type, String name, String scope, String bean) {
        if (group == null || type == null) {
            throw new IllegalArgumentException("Both group and type need to be specified");
        }
        if (name == null) {
            throw new IllegalArgumentException("Name needs to be specified");
        }
        this.group = group;
        this.type = type;
        this.name = name;
        this.scope = scope;
        this.bean = bean;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) { return true; }
        if (o == null || getClass() != o.getClass()) { return false; }
        final MetricName that = (MetricName) o;
        return bean.equals(that.bean);
    }

    @Override
    public int hashCode() {
        return bean.hashCode();
    }

    @Override
    public String toString() {
        return bean;
    }

    @Override
    public int compareTo(MetricName o) {
        return bean.compareTo(o.bean);
    }

    private static String createMBeanName(String group, String type, String name, String scope) {
        final StringBuilder nameBuilder = new StringBuilder();
        nameBuilder.append(group);
        nameBuilder.append(":type=");
        nameBuilder.append(type);
        if (scope != null) {
            nameBuilder.append(",scope=");
            nameBuilder.append(scope);
        }
        if (name.length() > 0) {
            nameBuilder.append(",name=");
            nameBuilder.append(name);
        }
        return nameBuilder.toString();
    }


*/

} // namespace medida

#endif // MEDIDA_METRIC_NAME_H_
