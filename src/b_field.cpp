#include "B_Field.h"
#include "R3Vectors.h"

B_Field_Vector::B_Field_Vector(double vx, double vy, double curr) {
    current = curr;
    this->direction = vectorR3(vx, vy, 0.0);
}

B_Field_Vector::B_Field_Vector(const vectorR3 &v, double curr) {
    this->direction = v;
}

/**
 * Find the magnetic field at the given position
 *
 * @param x, y, z the coordinates at which to compute the field
 * @return The magnetic field at the given position
 */
vectorR3 B_Field_Vector::compute_B_field(double x, double y, double z) {
    /*Given the x, y, and z components of the point, calculates the B-field vector at
     that point by ampere's law*/

    vectorR3 pos = vectorR3(x, y, z);
    vectorR3 R = direction.vector_project(pos) - pos; // Vector pointing from the position to the wire, normal to the wire

    vectorR3 B = R.cross(direction);
    B = B / B.getMagnitude(); //unit vector in direction of magnetic field
    B = B * MU0 * current / (2 * PI * R.getMagnitude());
    return B;
}