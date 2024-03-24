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

TEST(pointcharge, init) {
    vectorR3 pos(-3.0, 7.3, 20.1);
    PointCharge c1(pos, 3.3);
    EXPECT_EQ(c1.pos.x_component, -3.0);
    EXPECT_EQ(c1.pos.y_component, 7.3);
    EXPECT_EQ(c1.pos.z_component, 20.1);
    EXPECT_EQ(c1.charge, 3.3);
}


TEST(efieldtest, efield_1comp) {
    PointCharge c1(0.0, 0.0, 0.0, 1.0);
    PointCharge c2(0.0, 0.0, 0.0, -1.0);
    double ke = 1.0 / (4.0 * PI * EP0);
    vectorR3 loc(1.0, 0.0 , 0.0);
    vectorR3 e1 = c1.efield(loc);
    EXPECT_EQ(e1.x_component, ke);
    EXPECT_EQ(e1.y_component, 0.0);
    EXPECT_EQ(e1.z_component, 0.0);
    vectorR3 e2 = c2.efield(loc);
    EXPECT_EQ(e2.x_component, -ke);
    EXPECT_EQ(e2.y_component, 0.0);
    EXPECT_EQ(e2.z_component, 0.0);
}

TEST(efieldtest, efield_multcomp) {
    PointCharge c1(0.0, 0.0, 0.0, 1.0);
    PointCharge c2(0.0, 0.0, 0.0, -1.0);
    double ke = 1.0 / (4.0 * PI * EP0);
    vectorR3 e3 = c2.efield(vectorR3(1.0, 1.0, 1.0));
    vectorR3 e4 = c1.efield(vectorR3(1.0, 1.0, 1.0));
    double mag = e3.getMagnitude();
    double mag2 = e4.getMagnitude();
    EXPECT_EQ(mag, ke / 3);
    EXPECT_EQ(mag2, ke / 3);
    EXPECT_EQ(e3.x_component < 0, 1);
    EXPECT_EQ(e3.y_component < 0, 1);
    EXPECT_EQ(e3.z_component < 0, 1);
    EXPECT_EQ(e4.x_component > 0, 1);
    EXPECT_EQ(e4.y_component > 0, 1);
    EXPECT_EQ(e4.z_component > 0, 1);
}

TEST(bfieldtest, one_dimension) {
    B_Field_Vector wire(1, 0, 100); //100 amps along x axis

    //1 mm away
    vectorR3 b1 = wire.compute_B_field(0, 0, 0.001);
    vectorR3 b2 = wire.compute_B_field(0, 0.001, 0);
    vectorR3 B1(0, -0.02, 0);
    vectorR3 B2(0, 0, 0.02);

    EXPECT_EQ(B1, b1);
    EXPECT_EQ(B2, b2);
}

TEST(bfieldtest, two_dimensions) {
    B_Field_Vector wire(1, 0, 100); // 100 amps along x axis

    // 5 mm away
    vectorR3 b3 = wire.compute_B_field(0, 0.003, 0.004);
    vectorR3 B3(0, -0.0032, 0.0024);

    //account for overflow
    EXPECT_NEAR(B3.x_component, b3.x_component, 0.0000001);
    EXPECT_NEAR(B3.y_component, b3.y_component, 0.0000001);
    EXPECT_NEAR(B3.z_component, b3.z_component, 0.0000001);
}