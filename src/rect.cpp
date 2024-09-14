#include "rect.hpp"

Rect::Rect(glm::vec3 position, float width, float height, glm::vec4 color)
    : position(position),
      width(width),
      height(height),
      color(color) {}

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
    : position(x, y, z),
      width(width),
      height(height),
      color(r, g, b, a) {}

