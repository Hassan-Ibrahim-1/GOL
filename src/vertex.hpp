#pragma once

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position = glm::vec3(0);
    glm::vec4 color = glm::vec4(0);

    Vertex() = default;
    Vertex(glm::vec3 position, glm::vec4 color);
    Vertex(float x, float y, float z, float r, float g, float b, float a = 1.0f);
};

