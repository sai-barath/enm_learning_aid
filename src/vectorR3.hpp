#pragma once
#include <cmath>

const double TOL = 1e-5; // TODO
const double EP0 = 8.8542E-12; // Vacuum permittivity constant (C^2/(N*m^2))
const double MU0 = 1.2566E-6; // Vacuum permeability constant ((T*m)/A)
const double PI = 3.14159; // The first six digits of pi.

/**
 * A generic implementation of vectors.
 * 
 * Contains overloaded opeartors and usefule methods for vector operations.
*/
class vectorR3 { 
  public:
    double x_component; // x component of the vector
    double y_component; // y component of the vector
    double z_component; // z component of the vector

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
    
    vectorR3(const vectorR3& other);

    /**
     * Calculate the magnitude of the vector.
     * 
     * @return The magnitude of the vector.
    */
    double getMagnitude();

    /**
     * Calculate the squared magnitude of the vector.
     * 
     * Useful for operations that require the square of the
     * magnitude as it avoids unnecessary square roots.
     * 
     * @return The magnitude of the vector squared.
    */
    double magsquared();

    /**
     * Find the sum vector b and this vector.
     * 
     * Performs basic vector addition.
     * 
     * @param b The vector to add to this vector.
     * @return The sum of the two vectors.
    */
    vectorR3 add(const vectorR3& b);

    /**
     * Performs basic scalar multiplication.
     * 
     * @param c The scalar quantity by which to multiply the vector.
     * @return The scalar multiple of the vector.
    */
    vectorR3 scalar_multiply(double c);

    /**
     * Performs a basic scalar projection.
     * 
     * Projects b onto this vector.
     * 
     * @param b The vector to project onto this vector.
     * @return The result of the scalar projection.
    */
    double scalar_project(const vectorR3& b);

    /**
     * Performs a basic vector projection.
     * 
     * Projects b onto this vector.
     * 
     * @param b the vector to project onto this vector.
     * @return The result of the vector projection.
    */
    vectorR3 vector_project(const vectorR3 &b);

    /**
     * Performs a basic dot product of this vector and the given vector.
     * 
     * @param b The vector with which to perform the dot product.
     * @return The result of the dot product.
    */
    double dot(const vectorR3 &b);

    /**
     * Performs a basic cross product of this vector and the given vector.
     * 
     * @param b The vector with which to perform the cross product.
     * @return The result of the cross product.
    */
    vectorR3 cross(const vectorR3& b);

    /**
     * Make a deep copy of another vector to instantiate this vector.
     * 
     * @param other The vector of which to make the deep copy.
     * @return The new instantiated vector.
    */
    vectorR3& operator=(const vectorR3& other);

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
    vectorR3 operator+(const vectorR3& other);

    /**
     * Find the difference between this vector and another vector.
     *
     * Performs basic vector subtraction.
     *
     * @param other The vector to subtract from this vector.
     * @return The difference of the two vectors.
     */
    vectorR3 operator-(const vectorR3& other);

    /**
     * Performs basic scalar multiplication.
     *
     * @param scalar The scalar quantity by which to multiply the vector.
     * @return The scalar multiple of the vector.
     */
    vectorR3 operator*(const double& scalar);

    /**
     * Performs basic scalar division.
     * 
     * @param scalar The scalar quantity by which to divide the vector.
     * @return The resulting vector.
    */
    vectorR3 operator/(const double &scalar);

    /**
     * Performs a basic dot product of this vector and the given vector.
     *
     * @param Other The vector with which to perform the dot product.
     * @return The result of the dot product.
     */
    double operator*(const vectorR3& other);

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
};

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

vectorR3::vectorR3(const vectorR3& other) {
    this->x_component = other.x_component;
    this->y_component = other.y_component;
    this->z_component = other.z_component;
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

double vectorR3::scalar_project(const vectorR3 &b) {
    // Computes the scalar projection for b onto a
    return (this->dot(b) / (this->getMagnitude()));
}

vectorR3 vectorR3::vector_project(const vectorR3 &b) {
    // computes the vector projection for b onto a
    return *this * (this->dot(b) / this->magsquared());
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

vectorR3 vectorR3::operator/(const double &scalar) {
    // Overloaded operator / for scalar division
    return vectorR3(this->x_component / scalar, this->y_component / scalar, this->z_component / scalar);
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

void vectorR3::operator+=(const vectorR3& other) {
    this->x_component += other.x_component;
    this->y_component += other.y_component;
    this->z_component += other.z_component;
}