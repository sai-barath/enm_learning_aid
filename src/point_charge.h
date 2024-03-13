#pragma once
#include "R3Vectors.h"

class PointCharge {
    //Assumption: fixed in place
    public:
        vectorR3 pos;
        double charge;
        PointCharge(const vectorR3& p, double c);
        PointCharge(double x, double y, double z, double c);
        vectorR3 efield(const vectorR3& loc);
};