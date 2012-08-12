//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_UNIFORM_SAMPLE_H_
#define MEDIDA_UNIFORM_SAMPLE_H_

#include <array>
#include <memory>
#include <vector>
#include <cstdatomic>  // GCC 4.4
#include <cstdint>

#include "medida/sample.h"

namespace medida {

class UniformSample : public Sample {
public:
  UniformSample(std::uint32_t reservoirSize);
  ~UniformSample();
  virtual void clear();
  virtual std::uint64_t size() const;
  virtual void update(std::int64_t value);
  virtual Snapshot getSnapshot() const;
protected:
    static const int kBITS_PER_LONG = 63;
    const std::uint32_t size_;
    std::atomic<std::uint64_t> count_;
    std::unique_ptr<std::atomic<std::int64_t>[]> values_;
    std::int64_t nextLong(std::int64_t n) const;
};

} // namespace medida

#endif // MEDIDA_UNIFORM_SAMPLE_H_
