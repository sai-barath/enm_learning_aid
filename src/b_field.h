#pragma once
#include "R3Vectors.h"
class B_Field_Vector {

  private:
    double current; // Current through the wire in amperes
    vectorR3 direction; // v vector of the line, with components x and y

  public:
    B_Field_Vector::B_Field_Vector(double vx, double vy, double curr);
    B_Field_Vector::B_Field_Vector(const vectorR3 &v, double curr);
    vectorR3 B_Field_Vector::compute_B_field();

};