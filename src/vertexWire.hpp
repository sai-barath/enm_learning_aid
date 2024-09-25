#pragma once
#include "vectorR3.hpp"

/**
 * A wire with various vertices and straight-line segments in between
 */
class wireOfVertices {
  private:
    double current;
  public:
    std::vector<vectorR3> vertices;
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
    vectorR3 bField(const vectorR3& pos) const;
};

void wireOfVertices::addVertex(double xPos, double yPos) {
  vertices.push_back(vectorR3(xPos, yPos, 0.0));
}

vectorR3 wireOfVertices::bField(const vectorR3& pos) const {
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
  double currentConstant = (MU0 * this->current) / (4 * PI);
  for(int i = 0; i < numSides; i++) {
    vectorR3 currVertex = vertices[i];
    vectorR3 nextVertex = vertices[(i + 1) % numSides];
    vectorR3 dir = nextVertex - currVertex;
    // What follows is the solution of the Biot-Savart integral
    double integralConstant = (pos.yComponent * dir.xComponent) - (currVertex.yComponent * dir.xComponent) + (currVertex.xComponent * dir.yComponent) - (pos.xComponent * dir.yComponent); 
    double a = -dir.xComponent, b = pos.xComponent - currVertex.xComponent, c = -dir.yComponent, d = pos.yComponent - pos.yComponent;
    double bcAd = 1.0 / (((b * c) - (a * d)) * ((b * c) - (a * d)));
    double combinedConstant = integralConstant * currentConstant * bcAd;
    double numeratorOne = (a * a) + (a * b) + ((c + d) * c);
    double denomOne = std::sqrt((a + b) * (a + b) + (c + d) * (c + d));
    double numeratorTwo = (a * b) + (c * d);
    double denomTwo = std::sqrt((b * b) + (d * d));
    double zComp = combinedConstant * ((numeratorOne / denomOne) - (numeratorTwo / denomTwo));
    B.zComponent += zComp;
  }
  return B;
}