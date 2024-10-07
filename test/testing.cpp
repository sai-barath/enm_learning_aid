#include <gtest/gtest.h>
#include "vectorR3.hpp"
#include "pointCharge.hpp"
#include "bField.hpp"
#include "vertexWire.hpp"
#include <cmath>

TEST(vectorR3_tests, Bvector_setup) {
    vectorR3 vec(4.0, 3.0, 1.0);
    EXPECT_EQ(vec.xComponent, 4.0);
    EXPECT_EQ(vec.yComponent, 3.0);
    EXPECT_EQ(vec.zComponent, 1.0);
    vectorR3 vec2;
    EXPECT_EQ(vec2.xComponent, 0.0);
    EXPECT_EQ(vec2.yComponent, 0.0);
    EXPECT_EQ(vec2.zComponent, 0.0);
}

TEST(vectorR3_tests, cross_product) {
    vectorR3 vec1(4.0, 3.0, 1.0);
    vectorR3 vec2(-7.0, 3.0, 2.0);
    vectorR3 vec3 = vec1.cross(vec2);
    EXPECT_EQ(vec3.xComponent, 3.0);
    EXPECT_EQ(vec3.yComponent, -15.0);
    EXPECT_EQ(vec3.zComponent, 33.0);
    vectorR3 vec4(1.0, 2.0, 3.0);
    vectorR3 vec5(-1.0, -2.0, -3.0);
    vectorR3 vec6 = vec4.cross(vec5);
    EXPECT_EQ(vec6.xComponent, 0.0);
    EXPECT_EQ(vec6.yComponent, 0.0);
    EXPECT_EQ(vec6.zComponent, 0.0);
    vectorR3 vec7 = vec2.cross(vec1);
    EXPECT_EQ(vec7.xComponent, -3.0);
    EXPECT_EQ(vec7.yComponent, 15.0);
    EXPECT_EQ(vec7.zComponent, -33.0);
    vectorR3 vec8;
    vectorR3 vec9;
    vectorR3 vec10 = vec8.cross(vec9);
    EXPECT_EQ(vec10.xComponent, 0.0);
    EXPECT_EQ(vec10.yComponent, 0.0);
    EXPECT_EQ(vec10.zComponent, 0.0);
}

TEST(pointCharge, init) {
    vectorR3 pos(-3.0, 7.3, 20.1);
    pointCharge c1(pos, 3.3);
    EXPECT_EQ(c1.pos.xComponent, -3.0);
    EXPECT_EQ(c1.pos.yComponent, 7.3);
    EXPECT_EQ(c1.pos.zComponent, 20.1);
    EXPECT_EQ(c1.charge, 3.3);
}


TEST(efieldtest, efield_1comp) {
    pointCharge c1(0.0, 0.0, 0.0, 1.0);
    pointCharge c2(0.0, 0.0, 0.0, -1.0);
    double ke = 1.0 / (4.0 * PI * EP0);
    vectorR3 loc(1.0, 0.0 , 0.0);
    vectorR3 e1 = c1.efield(loc);
    EXPECT_EQ(e1.xComponent, ke);
    EXPECT_EQ(e1.yComponent, 0.0);
    EXPECT_EQ(e1.zComponent, 0.0);
    vectorR3 e2 = c2.efield(loc);
    EXPECT_EQ(e2.xComponent, -ke);
    EXPECT_EQ(e2.yComponent, 0.0);
    EXPECT_EQ(e2.zComponent, 0.0);
}

TEST(efieldtest, efield_multcomp) {
    pointCharge c1(0.0, 0.0, 0.0, 1.0);
    pointCharge c2(0.0, 0.0, 0.0, -1.0);
    double ke = 1.0 / (4.0 * PI * EP0);
    vectorR3 e3 = c2.efield(vectorR3(1.0, 1.0, 1.0));
    vectorR3 e4 = c1.efield(vectorR3(1.0, 1.0, 1.0));
    double mag = e3.magnitude();
    double mag2 = e4.magnitude();
    EXPECT_EQ(mag, ke / 3);
    EXPECT_EQ(mag2, ke / 3);
    EXPECT_EQ(e3.xComponent < 0, 1);
    EXPECT_EQ(e3.yComponent < 0, 1);
    EXPECT_EQ(e3.zComponent < 0, 1);
    EXPECT_EQ(e4.xComponent > 0, 1);
    EXPECT_EQ(e4.yComponent > 0, 1);
    EXPECT_EQ(e4.zComponent > 0, 1);
}

TEST(bfieldtest, one_dimension) {
    longThinWire wire(1, 0, 100); //100 amps along x axis

    //1 mm away
    vectorR3 b1 = wire.computeBField(vectorR3(0, 0, 0.001));
    vectorR3 b2 = wire.computeBField(vectorR3(0, 0.001, 0));
    vectorR3 B1(0, -0.02, 0);
    vectorR3 B2(0, 0, 0.02);

    EXPECT_NEAR(B1.xComponent, b1.xComponent, 0.00001);
    EXPECT_NEAR(B1.yComponent, b1.yComponent, 0.00001);
    EXPECT_NEAR(B1.zComponent, b1.zComponent, 0.00001);
    EXPECT_NEAR(B2.xComponent, b2.xComponent, 0.00001);
    EXPECT_NEAR(B2.yComponent, b2.yComponent, 0.00001);
    EXPECT_NEAR(B2.zComponent, b2.zComponent, 0.00001);
}

TEST(bfieldtest, two_dimensions) {
    longThinWire wire(1, 0, 100); // 100 amps along x axis

    // 5 mm away
    vectorR3 b3 = wire.computeBField(vectorR3(0, 0.003, 0.004));
    vectorR3 B3(vectorR3(0, -0.0032, 0.0024));

    //account for overflow
    EXPECT_NEAR(B3.xComponent, b3.xComponent, 0.0000001);
    EXPECT_NEAR(B3.yComponent, b3.yComponent, 0.0000001);
    EXPECT_NEAR(B3.zComponent, b3.zComponent, 0.0000001);
}

TEST(vwiretest, square) {
    wireOfVertices wir(1.0);
    wir.vertices.push_back(vectorR3(0, 0, 0));
    wir.vertices.push_back(vectorR3(100, 0, 0));
    wir.vertices.push_back(vectorR3(100, 100, 0));
    wir.vertices.push_back(vectorR3(0, 100, 0));
    vectorR3 p1 = wir.bField(vectorR3(50, 50, 0));
    vectorR3 p2 = wir.bField(vectorR3(150, 50, 0));
    vectorR3 p3 = wir.bField(vectorR3(50, 150, 0));
    vectorR3 p4 = wir.bField(vectorR3(150, 150, 0));
    EXPECT_NEAR(p1.zComponent, 0, 0.001);
    EXPECT_NEAR(p2.zComponent, 0, 0.001);
    EXPECT_NEAR(p3.zComponent, 0, 0.001);
    EXPECT_NEAR(p4.zComponent, 0, 0.001);
}