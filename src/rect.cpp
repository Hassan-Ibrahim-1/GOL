#include "rect.hpp"

Rect::Rect(Vertex v1, Vertex v2, Vertex v3, Vertex v4) {
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
    vertices[3] = v4;
}

Rect::Rect(glm::vec3 position, float width, float height, glm::vec4 color) {
    vertices[0] = Vertex(position, color);
    vertices[1] = Vertex(glm::vec3(position.x + width, position.y - height, position.z), color);
    vertices[2] = Vertex(glm::vec3(position.x, position.y - height, position.z), color);
    vertices[3] = Vertex(glm::vec3(position.x + width, position.y - height, position.z), color);
}

Rect::Rect(
    float x,
    float y,
    float z,
    float width,
    float height,
    float r,
    float g,
    float b,
    float a
)
    : Rect(glm::vec3(x, y, z), width, height, glm::vec4(r, g, b, a)) {}

