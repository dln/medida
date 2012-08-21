//
// Copyright (c) 2012 Daniel Lundin AB
//

#include <vector>

#include <gtest/gtest.h>

#include "medida/metric_name.h"

using namespace medida;


class MetricNameTest : public ::testing::Test {
protected:
  MetricNameTest() : name {"domain", "type", "name", "scope"} {
  };

  MetricName name;
};

TEST_F(MetricNameTest, hasADomain) {
  EXPECT_EQ(name.domain(), "domain");
}

TEST_F(MetricNameTest, hasAType) {
  EXPECT_EQ(name.type(), "type");
}

TEST_F(MetricNameTest, hasAName) {
  EXPECT_EQ(name.name(), "name");
}

TEST_F(MetricNameTest, hasAScope) {
  EXPECT_EQ(name.scope(), "scope");
  EXPECT_TRUE(name.has_scope());
}

TEST_F(MetricNameTest, isHumanReadable) {
  EXPECT_EQ(name.ToString(), "domain.type.name.scope");
}

TEST_F(MetricNameTest, hasAWorkingEqualsImplementation) {
  EXPECT_EQ(name, name);
  EXPECT_EQ(name, MetricName("domain", "type", "name", "scope"));
  EXPECT_NE(name, MetricName("domain", "type", "name"));
}
