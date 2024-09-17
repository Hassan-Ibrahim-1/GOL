#pragma once

#include "rect.hpp"
#include "renderer.hpp"
#include "common.hpp"
#include "cell.hpp"

namespace Sim {

inline Rect _rect;
inline Renderer* _renderer;
inline uint _ncells = 1435;
inline std::vector<Cell> _cells;

void init();
void run();
void end();

void create_grid();
void create_imgui_windows();
void render_cells();

}

