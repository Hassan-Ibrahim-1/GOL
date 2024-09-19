#include <GLFW/glfw3.h>

#include <cmath>
#include <glm/glm.hpp>

#include "sim.hpp"
#include "globals.hpp"
#include "imgui.h"
#include "utils.hpp"

void Sim::init() {
    Transform transform(glm::vec3(-0.28f, 0.0f, 0.0f), Rotation(), glm::vec3(1.39f, 1.89f, 1.0f));
    _rect = Rect(transform, glm::vec4(1));
    _renderer = Globals::renderer;
    init_direction_offsets();
    create_grid();
    spawn_initial_cells();
    _start_time = glfwGetTime();
}

void Sim::run() {
    static uint _prev_seed = _seed;

    create_imgui_windows();
    render_cells();

    /*if (_start_time + _time_offset < glfwGetTime()) {*/
    /*    _seed++;*/
    /*    reset();*/
    /*}*/
    if (_update_cells && _start_time + _time_offset < glfwGetTime()) {
        update(); // renders cells
        _start_time = glfwGetTime();
    }
    else if (!_update_cells) {
        if (_prev_seed != _seed) {
            _prev_seed = _seed;
            reset();
        }
    }
    /*render_cells();*/
    _renderer->draw_rect(_rect, DrawMode::LINE);
}

void Sim::end() {

}

void Sim::reset() {
    _cells.clear();
    _cell_fills.clear();
    init();
}

void Sim::create_imgui_windows() {
    ImGui::Begin("sim bg");
    ImGui::SetWindowSize("window", ImVec2(400, 250));

    ImGui::ColorEdit4("rect color", (float*)&_rect.color);
    ImGui::DragFloat2("rect position", (float*)&_rect.transform.position, 0.01f, -1.0f, 1.0f);
    ImGui::DragFloat2("rect scale", (float*)&_rect.transform.scale, 0.01f, -2.0f, 2.0f);
    ImGui::DragInt("num cells", (int*)&_ncells, 1, 1, 10000);
    ImGui::DragFloat("time offset", &_time_offset, 0.01f, 0.0f, 100.0f);
    ImGui::DragInt("seed", (int*)&_seed, 1, 0);
    if (!_update_cells && ImGui::Button("start")) {
        _update_cells = true;
    }
    if (_update_cells) {
        if (ImGui::Button("pause")) {
            _update_cells = false;
        }
    }

    if (ImGui::Button("reset")) {
        _update_cells = false;
        reset();
    }

    ImGui::Text("mouse_pos (%.3f, %.3f)", Globals::mouse_pos.x, Globals::mouse_pos.y);

    // fps
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / Globals::io->Framerate, Globals::io->Framerate);

    ImGui::End();
}

void Sim::create_grid() {
    _cells.clear();

    // Find the closest factors
    uint f1 = (uint) glm::sqrt(_ncells);
    while (_ncells % f1 != 0) {
        f1--;
    }
    // f2 > f1
    uint f2 = _ncells / f1; // along the width

    uint n_rows = 0;
    uint n_cols = 0;
    
    // put the larger factor amount of cells on the larger side
    if (_rect.transform.scale.x > _rect.transform.scale.y) {
        n_rows = f1 - 1;
        n_cols = f2 - 1;
    }
    else {
        n_rows = f2 - 1;
        n_cols = f1 - 1;
    }

    _cols = n_cols;
    _rows = n_rows;

    update_direction_offsets();

    Transform cell_t = Transform();
    cell_t.scale.x = _rect.transform.scale.x / n_cols;
    cell_t.scale.y = _rect.transform.scale.y / n_rows;

    // make cell go to the upper left corner
    cell_t.position.x = (-0.5 * _rect.transform.scale.x) + _rect.transform.position.x;
    // + here to make the cell go to the right
    cell_t.position.x += (cell_t.scale.x / 2);

    // - here to make the cell go downwards - opposite of vao coordinate
    cell_t.position.y = (0.5 * _rect.transform.scale.y) + _rect.transform.position.y;
    cell_t.position.y -= (cell_t.scale.y / 2);

    float original_xpos = cell_t.position.x;

    // render all cells
    for (uint i = 0; i < n_rows; i++) {
        for (uint j = 0; j < n_cols; j++) {
            _cells.push_back(Cell(cell_t, glm::vec4(1)));
            /*cell.fill = j % 2 == 0 && i % 3 == 0;*/
            /*cell.render();*/
            cell_t.position.x += cell_t.scale.x;
        }
        cell_t.position.x = original_xpos;
        cell_t.position.y -= cell_t.scale.y;
    }
    _cell_fills.resize(_cells.size());
}

void Sim::update() {
    for (size_t i = 0; i < _cells.size(); i++) {
        Cell& cell = _cells[i];
        uint n_neighbours = cell_neighbours(i);
        if (n_neighbours < 2) {
            _cell_fills[i] = false;
        }
        else if (n_neighbours == 3 || n_neighbours == 2) {
            if (!cell.fill){
                _cell_fills[i] = n_neighbours == 3;
            }
        }
        else if (n_neighbours > 3) {
            if (cell.fill) {
                _cell_fills[i] = false;
            }
        }
        /*if (n_neighbours > 3) {*/
        /*    cell.fill = false;*/
        /*}*/
        /*else if (n_neighbours == 3) {*/
        /*    cell.fill = true;*/
        /*}*/
        /*else if (n_neighbours == 2) {*/
        /*    // what*/
        /*    if (cell.fill) {*/
        /*        cell.fill = true;*/
        /*    }*/
        /*}*/
        /*else if (n_neighbours < 2) {*/
        /*    cell.fill = false;*/
        /*}*/
        /*cell.rect.color = _rect.color;*/
        /*cell.render();*/
    }
}
void Sim::render_cells() {
    for (size_t i = 0; i < _cells.size(); i++) {
        Cell& cell = _cells[i];
        cell.fill = _cell_fills[i];
        cell.rect.color = _rect.color;
        cell.render();
    }
}

void Sim::init_direction_offsets() {
    _direction_offsets[EAST] = 1;
    _direction_offsets[WEST] = -1;
}

void Sim::update_direction_offsets() {
    _direction_offsets[NORTH] = -_cols;
    _direction_offsets[SOUTH] = _cols;
    _direction_offsets[NORTH_EAST] = -_cols + 1;
    _direction_offsets[NORTH_WEST] = -_cols - 1;
    _direction_offsets[SOUTH_EAST] = _cols + 1;
    _direction_offsets[SOUTH_WEST] = _cols - 1;
}

void Sim::spawn_initial_cells() {
    float sc = abs(sin(_seed));
    for (int col = 0; col < _cols; col++) {
        uint index = col;
        // uint n_cells = sc * (index += );
        /*printf("n_cells: %u\nindex: %u\nsc: %f\n", n_cells, index, sc);*/
        while (index != -1) {
            /*printf("filling cell with index %u\n", index);*/
            /*_cell_fills[index] = sin(index + col + _rows * 7819) * sc > (sin(sin(_rows)));*/
            _cell_fills[index] = noise(sc * index / col, index) < noise(index, sc) + noise(sc, cos(sc));
            index = cell_south(index);
            /*n_cells--;*/
        }
    }
    /*uint mid = _cells.size() / 2;*/
    /*mid += 20;*/
    /*_cell_fills[mid] = true;*/
    /*_cell_fills[mid + _direction_offsets[NORTH]] = true;*/
    /*_cells[mid + _direction_offsets[EAST]].fill = true;*/
    /*_cell_fills[mid + _direction_offsets[WEST]] = true;*/
    /*_cell_fills[mid + _direction_offsets[SOUTH]] = true;*/
    /*_cell_fills[mid + _direction_offsets[NORTH_EAST]] = true;*/
    /*_cell_fills[mid + _direction_offsets[NORTH_WEST]] = true;*/
    /*_cell_fills[mid + _direction_offsets[SOUTH_EAST]] = true;*/
    /*_cells[mid + _direction_offsets[SOUTH_WEST]] = true;*/
}

float Sim::noise(int x, int y) {
    int n = x + y * 57;
    n = (n<<13) ^ n;
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589)
    & 0x7fffffff) / 1073741824.0); 
}

uint Sim::cell_neighbours(uint cell_index) {
    uint count = 0;
    if (cell_north(cell_index) != -1) {
        if (_cells[cell_north(cell_index)].fill) {
            count++;
        }
    }
    if (cell_south(cell_index) != -1) {
        if (_cells[cell_south(cell_index)].fill) {
            count++;
        }
    }
    if (cell_east(cell_index) != -1) {
        if (_cells[cell_east(cell_index)].fill) {
            count++;
        }
    }
    if (cell_west(cell_index) != -1) {
        if (_cells[cell_west(cell_index)].fill) {
            count++;
        }
    }
    if (cell_north_east(cell_index) != -1) {
        if (_cells[cell_north_east(cell_index)].fill) {
            count++;
        }
    }
    if (cell_north_west(cell_index) != -1) {
        if (_cells[cell_north_west(cell_index)].fill) {
            count++;
        }
    }
    if (cell_south_east(cell_index) != -1) {
        if (_cells[cell_south_east(cell_index)].fill) {
            count++;
        }
    }
    if (cell_south_west(cell_index) != -1) {
        if (_cells[cell_south_west(cell_index)].fill) {
            count++;
        }
    }

    return count;
}

int Sim::cell_north(uint cell_index) {
    uint index = cell_index + _direction_offsets[NORTH];
    if (index < 0 || index >= _cells.size()) {
        return -1;
    }
    return index;
}
int Sim::cell_south(uint cell_index) {
    uint index = cell_index + _direction_offsets[SOUTH];
    if (index < 0 || index >= _cells.size()) {
        return -1;
    }
    return index;
}
int Sim::cell_east(uint cell_index) {
    uint index = cell_index + _direction_offsets[EAST];
    if (index < 0 || index >= _cells.size()) {
        return -1;
    }
    return index;
}
int Sim::cell_west(uint cell_index) {
    uint index = cell_index + _direction_offsets[WEST];
    if (index < 0 || index >= _cells.size()) {
        return -1;
    }
    return index;
}

int Sim::cell_north_east(uint cell_index) {
    uint index = cell_index + _direction_offsets[NORTH_EAST];
    if (index < 0 || index >= _cells.size()) {
        return -1;
    }
    return index;
}
int Sim::cell_north_west(uint cell_index) {
    uint index = cell_index + _direction_offsets[NORTH_WEST];
    if (index < 0 || index >= _cells.size()) {
        return -1;
    }
    return index;
}
int Sim::cell_south_east(uint cell_index) {
    uint index = cell_index + _direction_offsets[SOUTH_EAST];
    if (index < 0 || index >= _cells.size()) {
        return -1;
    }
    return index;
}
int Sim::cell_south_west(uint cell_index) {
    uint index = cell_index + _direction_offsets[SOUTH_WEST];
    if (index < 0 || index >= _cells.size()) {
        return -1;
    }
    return index;
}
