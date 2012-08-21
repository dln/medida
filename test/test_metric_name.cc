//
// Copyright (c) 2012 Daniel Lundin AB
//

#include <vector>

#include <gtest/gtest.h>

#include "medida/metric_name.h"

using namespace medida;


class MetricNameTest : public ::testing::Test {
protected:
  MetricNameTest() : name {"group", "type", "name", "scope", "bean"} {
  };

  MetricName name;
};

TEST_F(MetricNameTest, hasAGroup) {
  EXPECT_EQ(name.getGroup(), "group");
}

TEST_F(MetricNameTest, hasAType) {
  EXPECT_EQ(name.getType(), "type");
}

TEST_F(MetricNameTest, hasAName) {
  EXPECT_EQ(name.getName(), "name");
}

TEST_F(MetricNameTest, hasAScope) {
  EXPECT_EQ(name.getScope(), "scope");
}

TEST_F(MetricNameTest, hasABean) {
  EXPECT_EQ(name.getBean(), "bean");
}

TEST_F(MetricNameTest, isHumanReadable) {
  EXPECT_EQ(name.toString(), "bean");
}
