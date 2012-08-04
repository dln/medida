//
// Copyright (c) 2012 Daniel Lundin AB
//

#include <vector>
#include <iostream>

#include <gtest/gtest.h>

#include "medida/ewma.h"

using namespace medida;

void elapseMinute(EWMA &ewma) {
  for (int i = 1; i <= 12; i++) { // 12 * 5s
    ewma.tick();
  }
}

TEST(EWMATest, aOneMinuteEWMAWithAValueOfThree) {
  auto ewma = EWMA::oneMinuteEWMA();
  ewma.update(3);
  ewma.tick();
  EXPECT_NEAR(0.6, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.22072766, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.08120117, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.02987224, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.01098938, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00404277, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00148725, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00054713, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00020128, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00007405, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00002724, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00001002, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00000369, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00000136, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00000050, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.00000018, ewma.getRatePerSecond(), 1e-6);
}

TEST(EWMATest, aFiveMinuteEWMAWithAValueOfThree) {
  auto ewma = EWMA::fiveMinuteEWMA();
  ewma.update(3);
  ewma.tick();
  EXPECT_NEAR(0.6, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.49123845, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.40219203, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.32928698, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.26959738, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.22072766, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.18071653, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.14795818, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.12113791, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.09917933, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.08120117, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.06648190, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.05443077, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.04456415, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.03648604, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.02987224, ewma.getRatePerSecond(), 1e-6);
}

TEST(EWMATest, aFifteenMinuteEWMAWithAValueOfThree) {
  auto ewma = EWMA::fifteenMinuteEWMA();
  ewma.update(3);
  ewma.tick();
  EXPECT_NEAR(0.6, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.56130419, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.52510399, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.49123845, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.45955700, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.42991879, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.40219203, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.37625345, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.35198773, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.32928698, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.30805027, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.28818318, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.26959738, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.25221023, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.23594443, ewma.getRatePerSecond(), 1e-6);
  elapseMinute(ewma);
  EXPECT_NEAR(0.22072766, ewma.getRatePerSecond(), 1e-6);
}