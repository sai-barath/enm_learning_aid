#pragma once
#include "R3Vectors.h"

class PointCharge {
    //Assumption: fixed in place
    private:
        double charge;
        vectorR3 pos;
    public:
        PointCharge(const vectorR3& p, double c);
        PointCharge(double x, double y, double z, double c);
        vectorR3 efield(const vectorR3& loc);
};