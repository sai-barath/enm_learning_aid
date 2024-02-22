#include "B_Field_Vector.h"
#include "R3Vectors.h"

B_Field_Vector::B_Field_Vector(double vx, double vy, double curr) {
    current = curr;
    this->direction = vectorR3(vx, vy, 0.0);
}

B_Field_Vector::B_Field_Vector(const vectorR3 &v, double curr) {
    this->direction = v;
}

vectorR3 B_Field_Vector::compute_B_field(double x, double y, double z) {
    /*Given the x, y, and z components of the point, calculates the B-field vector at
     that point by ampere's law*/
    
}