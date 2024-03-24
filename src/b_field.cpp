#include "B_Field.h"
#include "R3Vectors.h"

Long_Thin_Wire::Long_Thin_Wire(double vx, double vy, double curr) {
    current = curr;
    this->direction = vectorR3(vx, vy, 0.0);
}

Long_Thin_Wire::Long_Thin_Wire(const vectorR3 &v, double curr) {
    this->direction = v;
}

vectorR3 Long_Thin_Wire::compute_B_field(double x, double y, double z) {
    vectorR3 pos = vectorR3(x, y, z);
    vectorR3 R = direction.vector_project(pos) - pos; // Vector pointing from the position to the wire, normal to the wire

    vectorR3 B = R.cross(direction);
    B = B / B.getMagnitude(); //unit vector in direction of magnetic field
    B = B * MU0 * current / (2 * PI * R.getMagnitude());
    return B;
}