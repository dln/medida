//
// Copyright (c) 2012 Daniel Lundin AB
//

#include <vector>

#include <gtest/gtest.h>

#include "medida/uniform_sample.h"

using namespace medida;


TEST(UniformSampleTest, aSampleOf100OutOf1000Elements) {
  UniformSample sample(100);

  for (int i = 0; i < 1000; i++) {
    sample.update(i);
  }

  EXPECT_EQ(std::uint32_t(100), sample.size());

  auto vals = sample.getSnapshot().getValues();
  EXPECT_EQ(std::uint32_t(100), vals.size());

  for (auto it = vals.begin(); it != vals.end(); ++it) {
    EXPECT_TRUE(*it < 1000.0);
    EXPECT_TRUE(*it >= 0.0);
  }
}
