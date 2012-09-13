//
// Copyright (c) 2012 Daniel Lundin AB
//


#include "medida/stats/uniform_sample.h"

#include <gtest/gtest.h>

using namespace medida::stats;

TEST(UniformSampleTest, aSampleOf100OutOf1000Elements) {
  UniformSample sample = {100};

  for (auto i = 0; i < 1000; i++) {
    sample.update(i);
  }

  EXPECT_EQ(100, sample.size());

  auto vals = sample.getSnapshot().getValues();
  EXPECT_EQ(100, vals.size());

  for (auto it = vals.begin(); it != vals.end(); ++it) {
    EXPECT_TRUE(*it < 1000.0);
    EXPECT_TRUE(*it >= 0.0);
  }
}
