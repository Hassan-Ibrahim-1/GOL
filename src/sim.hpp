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

inline uint _ncells = 1980;
inline std::vector<Cell> _cells;
inline std::vector<bool> _cell_fills;
inline std::array<int, 8> _direction_offsets;
inline double _start_time = 0.0;
inline float _time_offset = 0.4f;
inline uint _cols = 0;
inline uint _rows = 0;

inline uint _seed = 2000;

inline bool _start = false;

void init();
void run();
void end();


void create_grid();
void create_imgui_windows();
void update();
void render_cells();
void init_direction_offsets();
void update_direction_offsets();
void spawn_initial_cells();

uint cell_neighbours(uint cell_index);

// return -1 if no cell exists
int cell_north(uint cell_index);
int cell_south(uint cell_index);
int cell_east(uint cell_index);
int cell_west(uint cell_index);
int cell_north_east(uint cell_index);
int cell_north_west(uint cell_index);
int cell_south_east(uint cell_index);
int cell_south_west(uint cell_index);

}

