#pragma once
#include "R3Vectors.h"

/**
 * Implementation of an infinitely long wire
 * 
 * Can be used to model the magnetic field at any point around the wire
 */
class Long_Thin_wire {

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
    Long_Thin_wire(double vx, double vy, double curr);

    /**
     * Instantiate an infinite wire
     *
     * @param v The direction of the wire, pointing in the direction of the current
     * @param curr The current in the wire measured in amperes
     */
    Long_Thin_wire(const vectorR3 &v, double curr);

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