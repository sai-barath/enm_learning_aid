#include <gtest/gtest.h>
#include "R3Vectors.h"
#include "point_charge.h"

TEST(vectorR3_tests, Bvector_setup) {
    vectorR3 vec(4.0, 3.0, 1.0);
    EXPECT_EQ(vec.x_component, 4.0);
    EXPECT_EQ(vec.y_component, 3.0);
    EXPECT_EQ(vec.z_component, 1.0);
}
