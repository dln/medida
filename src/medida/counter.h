//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_COUNTER_H_
#define MEDIDA_COUNTER_H_

#include <cstdatomic>
#include <cstddef>
#include <cstdint>

namespace medida {

class Counter {
//class Counter : public Metric {
public:
  Counter();
  ~Counter();
  void inc(std::int64_t n = 1);
  void dec(std::int64_t n = 1);
  std::int64_t getCount() const;
  void clear();

  // void processWith(MetricProcessor<T> processor MetricName name, T context) const;

  /*
    @Override
    public <T> void processWith(MetricProcessor<T> processor, MetricName name, T context) throws Exception {
        processor.processCounter(name, this, context);
    }};
*/
protected:
  std::atomic<std::int64_t> count_;
};

} // namespace medida

#endif // MEDIDA_COUNTER_H_
