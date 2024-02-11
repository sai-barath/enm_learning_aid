#include <cmath>
#include "R3Vectors.h"

vectorR3::vectorR3(double i, double j, double k) {
    x_component = i;
    y_component = j;
    z_component = k;
};

double vectorR3::getMagnitude() {
    return (sqrt((this->x_component * this->x_component) + (this->y_component * this->y_component) + (this->z_component * this->z_component)));
}

vectorR3 vectorR3::add(const vectorR3& b) {
    // Computes the vector sum of a and b and returns a vectorR3 object by adding components
    vectorR3 vector_sum(this->x_component + b.x_component, this->y_component + b.y_component, this->z_component + b.z_component);
    return vector_sum;
}

vectorR3 vectorR3::scalar_multiply(double c) {
    vectorR3 scalar_multiple(this->x_component * c, this->y_component * c, this->z_component * c);
    return scalar_multiple;
}

double vectorR3::dot(const vectorR3& b) {
    // Computes the scalar product of vectorR3 objects a and b
    return (this->x_component*b.x_component + this->y_component*b.y_component + this->z_component*b.z_component);
}

vectorR3 vectorR3::cross(const vectorR3& b) {
    // Computes the vector product of vectorR3 objects a and b according to the RHR
    vectorR3 cross_product(((this->y_component * b.z_component) - (this->z_component * b.y_component)),
        -((this->x_component * b.z_component) - (this->z_component * b.x_component)),
        ((this->x_component * b.y_component) - (this->y_component * b.x_component)));
    return cross_product;
}