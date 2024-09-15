#include "globals.hpp"

#include "cell.hpp"

Cell::Cell(Transform transform, glm::vec4 color)
    : rect(transform, color) {}

Cell::Cell(glm::vec3 position, glm::vec4 color) 
    : rect(position, color) {}

void Cell::render() {
    Globals::renderer->draw_rect(rect);
}

