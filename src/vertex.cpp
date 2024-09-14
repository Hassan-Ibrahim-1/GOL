#include "vertex.hpp"

Vertex::Vertex(glm::vec3 position, glm::vec4 color)
    : position(position),
      color(color) {}

Vertex::Vertex(float x, float y, float z, float r, float g, float b, float a)
    : position(glm::vec3(x, y, z)),
      color(glm::vec4(r, g, b, a)) {}

