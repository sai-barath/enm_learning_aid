#include "point_charge.h"
#include "R3Vectors.h"
#include <cmath>

PointCharge::PointCharge(const vectorR3& p, double c) {
    this->charge = c;
    this->pos = p;
}

PointCharge::PointCharge(double x, double y, double z, double c) {
    this->pos = vectorR3(x, y, z);
    this->charge = c;
}

vectorR3 PointCharge::efield(const vectorR3& loc) {
    vectorR3 dir = this->pos - loc;
    dir *= -1.0;
    double magdirection = dir.getMagnitude();
    double mag = (this->charge) / (4.0 * PI * EP0 * magdirection * magdirection);
    dir *= (mag / magdirection);
    return dir;
}
