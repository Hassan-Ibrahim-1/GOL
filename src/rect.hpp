#pragma once

#include <array>

#include <glm/glm.hpp>

#include "vertex.hpp"

struct Rect {
    std::array<Vertex, 4> vertices;

    Rect(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
    Rect(glm::vec3 position, float width, float height, glm::vec4 color);
    Rect(
        float x,
        float y,
        float z,
        float width,
        float height,
        float r,
        float g,
        float b,
        float a = 1.0f
    );
    Rect() = default;
};

