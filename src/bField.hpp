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
  public:
    vectorR3 direction; // The direction of the current in the infinite wire
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
     * @param pos the position
     * @return The magnetic field vector at the given position
     */
    vectorR3 computeBField(const vectorR3& pos) const;

};

longThinWire::longThinWire(double vx, double vy, double curr) {
    current = curr;
    this->direction = vectorR3(vx, vy, 0.0);
}

longThinWire::longThinWire(const vectorR3 &v, double curr) {
    this->direction = v;
}

vectorR3 longThinWire::computeBField(const vectorR3& pos) const {
    vectorR3 R = pos - direction.vectorProject(pos); // Vector pointing from the position to the wire, normal to the wire
    vectorR3 B = direction ^ R; // Initially has an incorrect magnitude
    B = B / B.magnitude(); //unit vector in direction of magnetic field
    B = B * MU0 * current / (2 * PI * R.magnitude());
    return B;
}