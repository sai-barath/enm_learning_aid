#pragma once

const double TOL = 1e-5;
class vectorR3 { 
  public:
    double x_component, y_component, z_component;

    vectorR3(double i, double j, double k);

    vectorR3();

    double getMagnitude();

    vectorR3 add(const vectorR3& b);

    vectorR3 scalar_multiply(double c);

    double dot(const vectorR3& b);

    vectorR3 cross(const vectorR3& b);

    vectorR3& operator=(const vectorR3& other);

    bool operator==(const vectorR3& other);

    vectorR3 operator+(const vectorR3& other);

    vectorR3 operator-(const vectorR3& other);

    double magsquared();
};