#pragma once
#include "vectorR3.hpp"

/**
 * A wire with various vertices and straight-line segments in between
 */
class wireOfVertices {
  private:
    double current;
    std::vector<vectorR3> vertices;
  public:
    /**
     * Create a wire of vertices
     * @param curr: The (equal) current in each segment of wire
     */
    wireOfVertices(double curr): current(curr) {}

    /**
     * Add a vertex
     * @param pos: The location of the vertex
     */
    void addVertex(vectorR3 pos);

    /**
     * Find the Magnetic field caused by the entire shape at a specific location
     * @param pos: The location
     * @return: The Magnetic field vector at pos
     */
    vectorR3 bField(const vectorR3& pos);
};