#pragma once
#include "vectorR3.hpp"

/**
 * Implementation of an infinitely long wire
 * 
 * Can be used to model the magnetic field at any point around the wire
 */
class longThinWire {

  private:
    double current; // Current through the wire in amperes
    vectorR3 direction; // The direction of the current in the infinite wire

  public:
    /**
     * Instantiate an infinite wire
     *
     * @param vx The x direction of the wire, pointing in the direction of the current
     * @param vy The y direction of the wire, pointing in the direciton of the current
     * @param curr The current in the wire measured in amperes
     */
    longThinWire(double vx, double vy, double curr);

    /**
     * Instantiate an infinite wire
     *
     * @param v The direction of the wire, pointing in the direction of the current
     * @param curr The current in the wire measured in amperes
     */
    longThinWire(const vectorR3 &v, double curr);

    /**
     * Find the magnetic field at the given location
     *
     * @param x The x coordinate of the location
     * @param y The y coordinate of the location
     * @param z The z coordinate of the location
     * @return The magnetic field vector at the given position
     */
    vectorR3 compute_B_field(double x, double y, double z);

};

longThinWire::longThinWire(double vx, double vy, double curr) {
    current = curr;
    this->direction = vectorR3(vx, vy, 0.0);
}

longThinWire::longThinWire(const vectorR3 &v, double curr) {
    this->direction = v;
}

vectorR3 longThinWire::compute_B_field(double x, double y, double z) {
    vectorR3 pos = vectorR3(x, y, z);
    vectorR3 R = direction.vectorProject(pos) - pos; // Vector pointing from the position to the wire, normal to the wire

    vectorR3 B = R.cross(direction);
    B = B / B.magnitude(); //unit vector in direction of magnetic field
    B = B * MU0 * current / (2 * PI * R.magnitude());
    return B;
}