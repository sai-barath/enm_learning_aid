#pragma once
#include <cmath>
#include <iostream>

const double TOL = 1e-5; // TODO
const double EP0 = 8.8542E-12; // Vacuum permittivity constant (C^2/(N*m^2))
const double MU0 = 1.2566E-6; // Vacuum permeability constant ((T*m)/A)
const double PI = 3.14159; // The first six digits of pi.
const double SQRT2 = 1.41421356237;
const double E = 2.718281828459;

/**
 * A generic implementation of vectors.
 * 
 * Contains overloaded opeartors and usefule methods for vector operations.
*/
class vectorR3 { 
  public:
    double xComponent; // x component of the vector
    double yComponent; // y component of the vector
    double zComponent; // z component of the vector

    /**
     * Instantiates a vector.
     * 
     * @param i The x component of the vector (in the direction of i).
     * @param j The y component of the vector (in the direction of j).
     * @param k The z component of the vector (in the direction of k).
    */
    vectorR3(double i, double j, double k);

    /**
     * Instantiates the vector <0.0, 0.0, 0.0>.
    */
    vectorR3();

    /**
     * Calculate the magnitude of the vector.
     * 
     * @return The magnitude of the vector.
    */
    double magnitude() const;

    /**
     * Calculate the squared magnitude of the vector.
     * 
     * Useful for operations that require the square of the
     * magnitude as it avoids unnecessary square roots.
     * 
     * @return The magnitude of the vector squared.
    */
    double magSquared() const;

    /**
     * Find the sum vector b and this vector.
     * 
     * Performs basic vector addition.
     * 
     * @param b The vector to add to this vector.
     * @return The sum of the two vectors.
    */
    vectorR3 add(const vectorR3& b) const;

    /**
     * Performs basic scalar multiplication.
     * 
     * @param c The scalar quantity by which to multiply the vector.
     * @return The scalar multiple of the vector.
    */
    vectorR3 scalarMultiply(double c) const;

    /**
     * Performs a basic scalar projection.
     * 
     * Projects b onto this vector.
     * 
     * @param b The vector to project onto this vector.
     * @return The result of the scalar projection.
    */
    double scalarProject(const vectorR3& b) const;

    /**
     * Performs a basic vector projection.
     * 
     * Projects b onto this vector.
     * 
     * @param b the vector to project onto this vector.
     * @return The result of the vector projection.
    */
    vectorR3 vectorProject(const vectorR3 &b) const;

    /**
     * Performs a basic dot product of this vector and the given vector.
     * 
     * @param b The vector with which to perform the dot product.
     * @return The result of the dot product.
    */
    double dot(const vectorR3 &b) const;

    /**
     * Performs a basic cross product of this vector and the given vector.
     * 
     * @param b The vector with which to perform the cross product.
     * @return The result of the cross product.
    */
    vectorR3 cross(const vectorR3& b) const;

    /**
     * Checks if this vector is the same as another vector.
     *
     * @param other The other vector with which to make the comparison.
     * @return A boolean value signifying whether the two vectors are equal.
     */
    bool operator==(const vectorR3& other);

    /**
     * Find the sum of this vector and another vector.
     *
     * Performs basic vector addition.
     *
     * @param other The vector to add to this vector.
     * @return The sum of the two vectors.
     */
    vectorR3 operator+(const vectorR3& other) const;

    /**
     * Find the difference between this vector and another vector.
     *
     * Performs basic vector subtraction.
     *
     * @param other The vector to subtract from this vector.
     * @return The difference of the two vectors.
     */
    vectorR3 operator-(const vectorR3& other) const;

    /**
     * Performs basic scalar multiplication.
     *
     * @param scalar The scalar quantity by which to multiply the vector.
     * @return The scalar multiple of the vector.
     */
    vectorR3 operator*(const double& scalar) const;

    /**
     * Performs basic scalar division.
     * 
     * @param scalar The scalar quantity by which to divide the vector.
     * @return The resulting vector.
    */
    vectorR3 operator/(const double &scalar) const;

    /**
     * Performs a basic dot product of this vector and the given vector.
     *
     * @param other The vector with which to perform the dot product.
     * @return The result of the dot product.
     */
    double operator*(const vectorR3& other) const;

    /**
     * Performs the cross product this X other
     * ^ used because the cross product is a wedge product
     * @param other The vector with which to perform the cross product.
     * @return The result of the cross product.
     */
    vectorR3 operator^(const vectorR3& other) const;

    /**
     * Performs basic scalar multiplication. Sets this vector equal to the resulting scalar multiple.
     *
     * @param scalar The scalar quantity by which to multiply the vector.
     */
    void operator*=(const double& scalar);

    /**
     * Adds other vector to this vector
     *
     * @param other The other vector
     */
    void operator+=(const vectorR3& other);

    /**
     * Operator overload for <<
     */
    friend std::ostream& operator<<(std::ostream& out, const vectorR3& vec);
};

vectorR3::vectorR3(double i, double j, double k) {
    xComponent = i;
    yComponent = j;
    zComponent = k;
}

vectorR3::vectorR3() {
    xComponent = 0.0;
    yComponent = 0.0;
    zComponent = 0.0;
}

double vectorR3::magnitude() const {
    return (std::sqrt((this->xComponent * this->xComponent) + (this->yComponent * this->yComponent) + (this->zComponent * this->zComponent)));
}

vectorR3 vectorR3::add(const vectorR3& b) const {
    // Computes the vector sum of a and b and returns a vectorR3 object by adding components
    vectorR3 vector_sum(this->xComponent + b.xComponent, this->yComponent + b.yComponent, this->zComponent + b.zComponent);
    return vector_sum;
}

vectorR3 vectorR3::scalarMultiply(double c) const {
    vectorR3 scalar_multiple(this->xComponent * c, this->yComponent * c, this->zComponent * c);
    return scalar_multiple;
}

double vectorR3::scalarProject(const vectorR3 &b) const {
    // Computes the scalar projection for b onto a
    return (this->dot(b) / (this->magnitude()));
}

vectorR3 vectorR3::vectorProject(const vectorR3 &b) const {
    // computes the vector projection for b onto a
    double factor = this->dot(b) / this->magSquared();
    return vectorR3(factor * this->xComponent, factor * this->yComponent, factor * this->yComponent);
}

double vectorR3::dot(const vectorR3& b) const {
    // Computes the scalar product of vectorR3 objects a and b
    return (this->xComponent*b.xComponent + this->yComponent*b.yComponent + this->zComponent*b.zComponent);
}

vectorR3 vectorR3::cross(const vectorR3& b) const {
    // Computes the vector product of vectorR3 objects a and b according to the RHR
    vectorR3 cross_product(((this->yComponent * b.zComponent) - (this->zComponent * b.yComponent)),
        -((this->xComponent * b.zComponent) - (this->zComponent * b.xComponent)),
        ((this->xComponent * b.yComponent) - (this->yComponent * b.xComponent)));
    return cross_product;
}

bool vectorR3::operator==(const vectorR3& other) {
    return (std::abs(this->xComponent - other.xComponent) < TOL) &&
        (std::abs(this->yComponent - other.yComponent) < TOL) &&
        (std::abs(this->zComponent - other.zComponent) < TOL);
}

vectorR3 vectorR3::operator+(const vectorR3& other) const {
    return vectorR3(this->xComponent + other.xComponent, this->yComponent + other.yComponent, this->zComponent + other.zComponent);
}

vectorR3 vectorR3::operator-(const vectorR3& other) const {
    return vectorR3(this->xComponent - other.xComponent, this->yComponent - other.yComponent, this->zComponent - other.zComponent);
}

double vectorR3::magSquared() const {
    return (this->xComponent * this->xComponent) + (this->yComponent * this->yComponent) + (this->zComponent * this->zComponent);
}

vectorR3 vectorR3::operator*(const double& scalar) const {
    // Overloaded operator * for scalar multiplication
    return vectorR3(this->xComponent * scalar, this->yComponent * scalar, this->zComponent * scalar);
}

vectorR3 vectorR3::operator/(const double &scalar) const {
    // Overloaded operator / for scalar division
    return vectorR3(this->xComponent / scalar, this->yComponent / scalar, this->zComponent / scalar);
}

double vectorR3::operator*(const vectorR3& other) const {
    // Overloaded operator * for dot product
    return (this->xComponent * other.xComponent) + (this->yComponent * other.yComponent) + (this->zComponent * other.zComponent);
}

vectorR3 vectorR3::operator^(const vectorR3& other) const {
    return vectorR3(((this->yComponent * other.zComponent) - (this->zComponent * other.yComponent)),
        -((this->xComponent * other.zComponent) - (this->zComponent * other.xComponent)),
        ((this->xComponent * other.yComponent) - (this->yComponent * other.xComponent)));
}

void vectorR3::operator*=(const double& scalar) {
    this->xComponent *= scalar;
    this->yComponent *= scalar;
    this->zComponent *= scalar;
}

void vectorR3::operator+=(const vectorR3& other) {
    this->xComponent += other.xComponent;
    this->yComponent += other.yComponent;
    this->zComponent += other.zComponent;
}

std::ostream& operator<<(std::ostream& out, const vectorR3& vec) {
    out << "(" << vec.xComponent << ", " << vec.yComponent << ", " << vec.zComponent << "), mag: " << vec.magnitude() << std::endl; 
    return out;
}