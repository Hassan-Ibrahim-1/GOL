#pragma once

#include "rect.hpp"
#include "renderer.hpp"
#include "common.hpp"

namespace Sim {

inline Rect _rect;
inline Renderer* _renderer;
inline uint n_cells = 120;

void init();
void run();
void end();

void create_rect_grid();
void create_imgui_windows();

}

