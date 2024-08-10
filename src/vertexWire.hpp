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
    void addVertex(double xPos, double yPos);

    /**
     * Find the Magnetic field caused by the entire shape at a specific location
     * @param pos: The location
     * @return: The Magnetic field vector at pos
     */
    vectorR3 bField(const vectorR3& pos);
};

void wireOfVertices::addVertex(double xPos, double yPos) {
  vertices.push_back(vectorR3(xPos, yPos, 0.0));
}

vectorR3 wireOfVertices::bField(const vectorR3& pos) {
  int numSides = vertices.size();
  if(vertices.size() < 3) {
    std::cout << "Not enough vertices in wire shape, returning 0 vector" << std::endl;
    return vectorR3();
  }
  vectorR3 B;
  /**
   * Compute the component of the b-Field due to the segment of wire starting at vertex i; 
   * if last vertex, the wire goes back to the first
   **/
  for(int i = 0; i < numSides; i++) {
    vectorR3 dir = vertices[(i + 1) % numSides] - vertices[i];
  }
  return B;
}