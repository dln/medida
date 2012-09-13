//
// Copyright (c) 2012 Daniel Lundin AB
//

#include "medida/stats/snapshot.h"

#include <gtest/gtest.h>

using namespace medida::stats;

class SnapshotTest : public ::testing::Test {
protected:
  SnapshotTest() : values {5, 1, 2, 3, 4}, snapshot {values} {
  };
  const std::vector<double> values;
  const Snapshot snapshot;
};

TEST_F(SnapshotTest, smallQuantilesAreTheFirstValue) {
  EXPECT_DOUBLE_EQ(1, snapshot.getValue(0.0));
}

TEST_F(SnapshotTest, bigQuantilesAreTheLastValue) {
  EXPECT_DOUBLE_EQ(5, snapshot.getValue(1.0));
}

TEST_F(SnapshotTest, hasAMedian) {
  EXPECT_DOUBLE_EQ(3, snapshot.getMedian());
}

TEST_F(SnapshotTest, hasAp75) {
  EXPECT_DOUBLE_EQ(4.5, snapshot.get75thPercentile());
}

TEST_F(SnapshotTest, hasAp95) {
  EXPECT_DOUBLE_EQ(5.0, snapshot.get95thPercentile());
}

TEST_F(SnapshotTest, hasAp98) {
  EXPECT_DOUBLE_EQ(5.0, snapshot.get98thPercentile());
}

TEST_F(SnapshotTest, hasAp99) {
  EXPECT_DOUBLE_EQ(5.0, snapshot.get99thPercentile());
}

TEST_F(SnapshotTest, hasAp999) {
  EXPECT_DOUBLE_EQ(5.0, snapshot.get999thPercentile());
}

TEST_F(SnapshotTest, hasValues) {
  auto ref = {1.0, 2.0, 3.0, 4.0, 5.0};
  EXPECT_TRUE(std::equal(ref.begin(), ref.end(), snapshot.getValues().begin()));
}

TEST_F(SnapshotTest, hasASize) {
  EXPECT_EQ(5, snapshot.size());
}

TEST_F(SnapshotTest, canAlsoBeCreatedFromACollectionOfInt64) {
  auto expected_doubles = {1.0, 2.0, 3.0, 4.0, 5.0};
  auto vector_int64 = std::vector<std::int64_t> {1LL, 2LL, 3LL, 4LL, 5LL};
  Snapshot snapshot {vector_int64};
  EXPECT_TRUE(std::equal(expected_doubles.begin(), expected_doubles.end(), snapshot.getValues().begin()));
}

TEST_F(SnapshotTest, canAlsoBeCreatedFromACollectionOfAtomicInt64) {
  auto expected_doubles = {1.0, 2.0, 3.0, 4.0, 5.0};
  auto ints = {1L, 2L, 3L, 4L, 5L};
  auto atomics = std::vector<std::atomic<std::int64_t>>(ints.begin(), ints.end());
  Snapshot snapshot {atomics};
  EXPECT_TRUE(std::equal(expected_doubles.begin(), expected_doubles.end(), snapshot.getValues().begin()));
}
