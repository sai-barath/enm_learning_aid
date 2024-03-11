#include <gtest/gtest.h>
#include "R3Vectors.h"
#include "point_charge.h"
#include "b_field.h"
#include <cmath>

TEST(vectorR3_tests, Bvector_setup) {
    vectorR3 vec(4.0, 3.0, 1.0);
    EXPECT_EQ(vec.x_component, 4.0);
    EXPECT_EQ(vec.y_component, 3.0);
    EXPECT_EQ(vec.z_component, 1.0);
    vectorR3 vec2;
    EXPECT_EQ(vec2.x_component, 0.0);
    EXPECT_EQ(vec2.y_component, 0.0);
    EXPECT_EQ(vec2.z_component, 0.0);
}

TEST(vectorR3_tests, cross_product) {
    vectorR3 vec1(4.0, 3.0, 1.0);
    vectorR3 vec2(-7.0, 3.0, 2.0);
    vectorR3 vec3 = vec1.cross(vec2);
    EXPECT_EQ(vec3.x_component, 3.0);
    EXPECT_EQ(vec3.y_component, -15.0);
    EXPECT_EQ(vec3.z_component, 33.0);
    vectorR3 vec4(1.0, 2.0, 3.0);
    vectorR3 vec5(-1.0, -2.0, -3.0);
    vectorR3 vec6 = vec4.cross(vec5);
    EXPECT_EQ(vec6.x_component, 0.0);
    EXPECT_EQ(vec6.y_component, 0.0);
    EXPECT_EQ(vec6.z_component, 0.0);
    vectorR3 vec7 = vec2.cross(vec1);
    EXPECT_EQ(vec7.x_component, -3.0);
    EXPECT_EQ(vec7.y_component, 15.0);
    EXPECT_EQ(vec7.z_component, -33.0);
    vectorR3 vec8;
    vectorR3 vec9;
    vectorR3 vec10 = vec8.cross(vec9);
    EXPECT_EQ(vec10.x_component, 0.0);
    EXPECT_EQ(vec10.y_component, 0.0);
    EXPECT_EQ(vec10.z_component, 0.0);
}

TEST(efieldtest, efield) {
    PointCharge c1(0.0, 0.0, 0.0, 1.0);
    vectorR3 loc(1.0, 0.0 , 0.0);
    vectorR3 e1 = c1.efield(loc);
    double ke = 1.0 / (4.0 * PI * EP0);
    EXPECT_EQ(e1.x_component, ke);
    EXPECT_EQ(e1.y_component, 0.0);
    EXPECT_EQ(e1.z_component, 0.0);
    PointCharge c2(0.0, 0.0, 0.0, -1.0);
    vectorR3 e2 = c2.efield(loc);
    EXPECT_EQ(e2.x_component, -ke);
    EXPECT_EQ(e2.y_component, 0.0);
    EXPECT_EQ(e2.z_component, 0.0);
    vectorR3 e3 = c2.efield(vectorR3(1.0, 1.0, 1.0));
    EXPECT_EQ(e2.x_component, -(ke / std::sqrtf(3.0)));
    EXPECT_EQ(e2.y_component, -(ke / std::sqrtf(3.0)));
    EXPECT_EQ(e2.z_component, -(ke / std::sqrtf(3.0)));
}

