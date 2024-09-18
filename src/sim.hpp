#pragma once

#include "rect.hpp"
#include "renderer.hpp"
#include "common.hpp"
#include "cell.hpp"

namespace Sim {

enum Direction {
    NORTH = 0,
    SOUTH,
    EAST,
    WEST,
    NORTH_EAST,
    NORTH_WEST,
    SOUTH_EAST,
    SOUTH_WEST
};

inline Rect _rect;
inline Renderer* _renderer;

inline uint _ncells = 1435;
inline std::vector<Cell> _cells;
inline std::array<int, 8> _direction_offsets;

void init();
void run();
void end();


void create_grid();
void create_imgui_windows();
void update();
void render_cells();
void init_direction_offsets();
void update_direction_offsets(uint n_cols, uint n_rows);
void spawn_initial_cells();

}

