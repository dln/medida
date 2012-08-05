//
// Copyright (c) 2012 Daniel Lundin AB
//

#include <vector>

#include <gtest/gtest.h>

#include "medida/snapshot.h"

using namespace medida;


class SnapshotTest : public ::testing::Test {
protected:
  SnapshotTest() : values {5, 1, 2, 3, 4}, snapshot {values} {
  };

  const std::vector<double> values;
  const Snapshot snapshot;
};

TEST_F(SnapshotTest, smallQuantilesAreTheFirstValue) {
  EXPECT_DOUBLE_EQ(snapshot.getValue(0.0), 1);
}

TEST_F(SnapshotTest, bigQuantilesAreTheLastValue) {
  EXPECT_DOUBLE_EQ(snapshot.getValue(1.0), 5);
}

TEST_F(SnapshotTest, hasAMedian) {
  EXPECT_DOUBLE_EQ(snapshot.getMedian(), 3);
}

TEST_F(SnapshotTest, hasAp75) {
  EXPECT_DOUBLE_EQ(snapshot.get75thPercentile(), 4.5);
}

TEST_F(SnapshotTest, hasAp95) {
  EXPECT_DOUBLE_EQ(snapshot.get95thPercentile(), 5.0);
}

TEST_F(SnapshotTest, hasAp98) {
  EXPECT_DOUBLE_EQ(snapshot.get98thPercentile(), 5.0);
}

TEST_F(SnapshotTest, hasAp99) {
  EXPECT_DOUBLE_EQ(snapshot.get99thPercentile(), 5.0);
}

TEST_F(SnapshotTest, hasAp999) {
  EXPECT_DOUBLE_EQ(snapshot.get999thPercentile(), 5.0);
}

TEST_F(SnapshotTest, hasValues) {
  auto ref {1.0, 2.0, 3.0, 4.0, 5.0};
  EXPECT_TRUE(std::equal(ref.begin(), ref.end(), snapshot.getValues().begin()));
}

TEST_F(SnapshotTest, hasASize) {
  EXPECT_EQ(snapshot.size(), std::size_t(5));
}

TEST_F(SnapshotTest, canAlsoBeCreatedFromACollectionOfLongs) {
  auto ref_long {5L, 1L, 2L, 4L, 3L};
  auto ref_doubles {1.0, 2.0, 3.0, 4.0, 5.0};
  Snapshot snap {ref_long};
  EXPECT_TRUE(std::equal(ref_doubles.begin(), ref_doubles.end(), snap.getValues().begin()));
}
