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

TEST_F(MetricNameTest, hasAWorkingEquals) {
  EXPECT_EQ(name, name);
  EXPECT_EQ(name, MetricName("domain", "type", "name", "scope"));
  EXPECT_NE(name, MetricName("domain", "type", "name"));
}

TEST_F(MetricNameTest, hasAWorkingLessThan) {
  EXPECT_FALSE(MetricName("a", "a", "a") < MetricName("a", "a", "a"));

  EXPECT_FALSE(MetricName("a", "a", "b") < MetricName("a", "a", "a"));
  EXPECT_FALSE(MetricName("a", "b", "a") < MetricName("a", "a", "a"));
  EXPECT_FALSE(MetricName("b", "a", "b") < MetricName("a", "a", "a"));
  EXPECT_FALSE(MetricName("a", "a", "a", "a") < MetricName("a", "a", "a"));

  EXPECT_TRUE(MetricName("a", "a", "a") < MetricName("b", "a", "a"));
  EXPECT_TRUE(MetricName("a", "a", "a") < MetricName("a", "b", "a"));
  EXPECT_TRUE(MetricName("a", "a", "a") < MetricName("a", "a", "b"));
  EXPECT_TRUE(MetricName("a", "a", "a") < MetricName("a", "a", "a", "a"));
}

TEST_F(MetricNameTest, hasAWorkingGreaterThan) {
  EXPECT_FALSE(MetricName("a", "a", "a") > MetricName("a", "a", "a"));

  EXPECT_TRUE(MetricName("a", "a", "b") > MetricName("a", "a", "a"));
  EXPECT_TRUE(MetricName("a", "b", "a") > MetricName("a", "a", "a"));
  EXPECT_TRUE(MetricName("b", "a", "b") > MetricName("a", "a", "a"));
  EXPECT_TRUE(MetricName("a", "a", "a", "a") > MetricName("a", "a", "a"));

  EXPECT_FALSE(MetricName("a", "a", "a") > MetricName("b", "a", "a"));
  EXPECT_FALSE(MetricName("a", "a", "a") > MetricName("a", "b", "a"));
  EXPECT_FALSE(MetricName("a", "a", "a") > MetricName("a", "a", "b"));
  EXPECT_FALSE(MetricName("a", "a", "a") > MetricName("a", "a", "a", "a"));
}