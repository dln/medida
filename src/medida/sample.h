//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRICS_SAMPLE_H_
#define MEDIDA_METRICS_SAMPLE_H_

#include <cstddef>

#include "medida/snapshot.h"

namespace medida {

class Sample {
public:
  Sample();
  ~Sample();
  virtual void clear() = 0;
  virtual std::size_t size() const = 0;
  virtual void update(long value) = 0;
  virtual Snapshot getSnapshot() = 0;
protected:
};

}

#endif // MEDIDA_METRICS_SAMPLE_H_
