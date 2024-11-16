#pragma once
#include "vectorR3.hpp"

/**
 * Representation of a flat, thin disk in the plane with a unifom chargeDensity
 */
class disk {
    public:
        vectorR3 center;
        double rad;
        double chargeDensity;
        /**
         * @param c: the center
         * @param r: radius in meters
         * @param cd: constant charge density in C/m^2
         */
        disk(const vectorR3& c, double r, double cd) {
            this->center = c;
            this->rad = r;
            this->chargeDensity = cd;
        }
        disk() = default;
        /**
         * @param pos: The position
         */
        vectorR3 efield(const vectorR3& pos) {
            return vectorR3(10.0, 10.0, 0.0);
        }
};