//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/histogram.h"

#include <cmath>

#include "glog/logging.h"

#include "medida/stats/exp_decay_sample.h"
#include "medida/stats/uniform_sample.h"

namespace medida {

Histogram::Histogram(SampleType sample_type) {
  DLOG(INFO) << "Histogram " << this << " created. sample_type=" << sample_type;
  if (sample_type == SampleType::kUniform) {
    sample_ = std::unique_ptr<stats::Sample>(new stats::UniformSample(kDefaultSampleSize));
  } else if (sample_type == SampleType::kBiased) {
    sample_ = std::unique_ptr<stats::Sample>(new stats::ExpDecaySample(kDefaultSampleSize, kDefaultAlpha));
  } else {
    throw std::invalid_argument("invalid sample_type=" + sample_type);
  }
  Clear();
}

Histogram::~Histogram() {
  DLOG(INFO) << "Histogram " << this << " destroyed";
}

void Histogram::Process(const MetricProcessor& processor) const  {
  DLOG(INFO) << "Processing Histogram " << this;
  processor.Process(*this);
}

void Histogram::Clear() {
  min_ = 0;
  max_ = 0;
  sum_ = 0;
  count_ = 0;
  variance_m_ = 0.0;
  variance_s_ = 0.0;
  sample_->Clear();
}

void Histogram::Update(std::int64_t value) {
  sample_->Update(value);
  set_max(value);
  set_min(value);
  sum_ += value;
  count_++;
  UpdateVariance(value);
}

std::uint64_t Histogram::count() const {
  return count_.load();
}

double Histogram::sum() const {
  return sum_.load();
}

double Histogram::max() const {
  if (count() > 0) {
    return max_.load();
  }
  return 0.0;
}

double Histogram::min() const {
  if (count() > 0) {
    return min_.load();
  }
  return 0.0;
}

double Histogram::mean() const {
  if (count() > 0) {
    return sum_ / (double)count();
  }
  return 0.0;
}

double Histogram::std_dev() const {
  if (count() > 0) {
    return std::sqrt(variance());
  }
  return 0.0;
}

double Histogram::variance() const {
  auto c = count();
  if (c <= 1) {
    return 0.0;
  }
  return variance_s_ / (c - 1.0);
}

stats::Snapshot Histogram::GetSnapshot() const {
  return sample_->MakeSnapshot();
}

inline void Histogram::set_max(std::int64_t potential_max) {
  if (count_ > 0) {
    auto cur_max = max_.load();
    auto done = false;
    while (!done) {
      done = cur_max >= potential_max || max_.compare_exchange_weak(cur_max, potential_max);
    }
  } else {
    max_ = potential_max;
  }
  DLOG(INFO) << "Histogram::set_max: max=" << max_;
}

inline void Histogram::set_min(std::int64_t potential_min) {
  if (count_ > 0) {
    auto cur_min = min_.load();
    auto done = false;
    while (!done) {
      done = cur_min <= potential_min || min_.compare_exchange_weak(cur_min, potential_min);
    }
  } else {
    min_ = potential_min;
  }
  DLOG(INFO) << "Histogram::set_min: min=" << min_;
}

void Histogram::UpdateVariance(std::int64_t value) {
  std::lock_guard<std::mutex> lock {variance_mutex_};
  auto old_vm = variance_m_;
  auto old_vs = variance_s_;
  auto c = count();
  if (c == 1) {
    variance_m_ = 1.0;
  } else {
    variance_m_ = old_vm + (value - old_vm) / c;
    variance_s_ = old_vs + (value - old_vm) * (value - variance_m_);
  }
}

} // namespace medida