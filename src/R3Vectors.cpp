#include <cmath>
#include "R3Vectors.h"

vectorR3::vectorR3(double i, double j, double k) {
    x_component = i;
    y_component = j;
    z_component = k;
}

vectorR3::vectorR3() {
    x_component = 0.0;
    y_component = 0.0;
    z_component = 0.0;
}

double vectorR3::getMagnitude() {
    return (std::sqrt((this->x_component * this->x_component) + (this->y_component * this->y_component) + (this->z_component * this->z_component)));
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

vectorR3& vectorR3::operator=(const vectorR3& a) {
    if(this != &a) {
        this->x_component = a.x_component;
        this->y_component = a.y_component;
        this->z_component = a.z_component;
    }
    return *this;
}

bool vectorR3::operator==(const vectorR3& other) {
    return (std::abs(this->x_component - other.x_component) < TOL) &&
        (std::abs(this->y_component - other.y_component) < TOL) &&
        (std::abs(this->z_component - other.z_component) < TOL);
}

vectorR3 vectorR3::operator+(const vectorR3& other) {
    return vectorR3(this->x_component + other.x_component, this->y_component + other.y_component, this->z_component + other.z_component);
}

vectorR3 vectorR3::operator-(const vectorR3& other) {
    return vectorR3(this->x_component - other.x_component, this->y_component - other.y_component, this->z_component - other.z_component);
}

double vectorR3::magsquared() {
    return (this->x_component * this->x_component) + (this->y_component) + (this->z_component);
}

vectorR3 vectorR3::operator*(const double& scalar) {
    // Overloaded operator * for scalar multiplication
    return vectorR3(this->x_component * scalar, this->y_component * scalar, this->z_component * scalar);
}

double vectorR3::operator*(const vectorR3& other) {
    // Overloaded operator * for dot product
    return (this->x_component * other.x_component) + (this->y_component * other.y_component) + (this->z_component * other.z_component);
}

void vectorR3::operator*=(const double& scalar) {
    this->x_component *= scalar;
    this->y_component *= scalar;
    this->z_component *= scalar;
}