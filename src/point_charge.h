#pragma once
#include "R3Vectors.h"

class PointCharge {
    //Assumption: fixed in place
    private:
        double charge;
        vectorR3 pos;
    public:
        vectorR3 Efield(const vectorR3& pos);
};