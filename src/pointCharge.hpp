#pragma once
#include "vectorR3.hpp"
#include <cmath>

class pointCharge {
    //Assumption: fixed in place
    public:
        vectorR3 pos;
        double charge;
        pointCharge(const vectorR3& p, double c);
        pointCharge(double x, double y, double z, double c);
        vectorR3 efield(const vectorR3& loc);
};

pointCharge::pointCharge(const vectorR3& p, double c) {
    this->charge = c;
    this->pos = p;
}

pointCharge::pointCharge(double x, double y, double z, double c) {
    this->pos = vectorR3(x, y, z);
    this->charge = c;
}

vectorR3 pointCharge::efield(const vectorR3& loc) {
    vectorR3 dir = this->pos - loc;
    dir *= -1.0;
    double magdirection = dir.magnitude();
    double mag = (this->charge) / (4.0 * PI * EP0 * magdirection * magdirection);
    dir *= (mag / magdirection);
    return dir;
}