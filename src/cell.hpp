#pragma once

#include <glm/glm.hpp>

#include "rect.hpp"

struct Cell {
    Rect rect;
    bool fill = false;

    Cell() = default;
    Cell(Transform transform, glm::vec4 color);
    Cell(glm::vec3 position, glm::vec4 color);

    void render();
};

