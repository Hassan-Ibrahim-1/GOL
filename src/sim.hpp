#pragma once

#include "rect.hpp"
#include "renderer.hpp"
#include "common.hpp"

namespace Sim {

inline Rect _rect;
inline Renderer* _renderer;
inline uint n_cells = 120;
inline glm::vec3 cell_pos = glm::vec3(0);
inline glm::vec3 cell_scale = glm::vec3(1);

void init();
void run();
void end();

void create_rect_grid();
void create_imgui_windows();

}

