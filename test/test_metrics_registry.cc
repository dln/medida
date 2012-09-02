//
// Copyright (c) 2012 Daniel Lundin AB
//

#include "medida/metrics_registry.h"

#include <vector>

#include <gtest/gtest.h>


using namespace medida;


class MetricsRegistryTest : public ::testing::Test {
protected:
  MetricsRegistryTest() {
  };

  MetricsRegistry registry;
};

TEST_F(MetricsRegistryTest, keysByName) {
  Counter& abc = registry.NewCounter({"a", "b", "c"});
  Counter& abc2 = registry.NewCounter({"a", "b", "c"});
  Counter& abcd = registry.NewCounter({"a", "b", "c", "d"});
  EXPECT_EQ(abc.count(), 0) << "Counter a.b.c was not initialied to 0";
  EXPECT_EQ(&abc, &abc2) << "Counter a.b.c was created twice";
  EXPECT_NE(&abc, &abcd) << "Counter a.b.c and a.b.c.d are the same object";
}
