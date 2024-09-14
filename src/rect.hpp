#pragma once

#include <glm/glm.hpp>

struct Rect {
    glm::vec3 position = glm::vec3(0);
    float width = 1.0f;
    float height = 1.0f;

    glm::vec4 color = glm::vec4(0);

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

