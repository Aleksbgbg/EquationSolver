#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

#include "core/math/Matrix.h"

namespace {

using ::testing::Eq;

}  // namespace

TEST(MatrixTest, TestReducedRowExchelonForm) {
  const MatrixDef matrix({{-7, -6, -12, -33}, {5, 5, 7, 24}, {1, 0, 4, 5}});

  const auto rref = matrix.ReducedRowEchelonForm();
  std::cout << rref;

  EXPECT_THAT(rref, Eq(MatrixDef({{1, 0, 0, -3}, {0, 1, 0, 5}, {0, 0, 1, 2}})));
}
