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

std::uint64_t Histogram::count() const {
  return count_;
}

double Histogram::sum() const {
  return sum_.load();
}

double Histogram::max() const {
  if (count_ > 0) {
    return max_.load();
  }
  return 0.0;
}

double Histogram::min() const {
  if (count_ > 0) {
    return min_.load();
  }
  return 0.0;
}

double Histogram::mean() const {
  if (count_ > 0) {
    return sum_ / (double)count_;
  }
  return 0.0;
}

double Histogram::std_dev() const {
  if (count_ > 0) {
    return std::sqrt(variance());
  }
  return 0.0;
}

double Histogram::variance() const {
  auto c = count();
  if (c > 1) {
    std::lock_guard<std::mutex> lock {variance_mutex_};
    return variance_s_ / (c - 1.0);
  } 
  return 0.0;
}

stats::Snapshot Histogram::GetSnapshot() const {
  return sample_->MakeSnapshot();
}


void Histogram::Update(std::int64_t value) {
  sample_->Update(value);
  if (count_ > 0) {
    auto cur_max = max_.load();
    auto cur_min = min_.load();
    while (cur_max < value && !max_.compare_exchange_weak(cur_max, value)) {
      // Spin until max is updated
    }
    while(cur_min > value && !min_.compare_exchange_weak(cur_min, value)) {
      // Spin until min is updated
    }
  } else {
    max_ = value;
    min_ = value;
  }
  sum_ += value;
  auto new_count = ++count_;
  std::lock_guard<std::mutex> lock {variance_mutex_};
  auto old_vm = variance_m_;
  auto old_vs = variance_s_;
  if (new_count > 1) {
    variance_m_ = old_vm + (value - old_vm) / new_count;
    variance_s_ = old_vs + (value - old_vm) * (value - variance_m_);
  } else {
    variance_m_ = 1.0;
  }
}


} // namespace medida