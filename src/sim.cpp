#include <glm/glm.hpp>

#include "sim.hpp"
#include "globals.hpp"
#include "imgui.h"

void Sim::init() {
    Transform transform(glm::vec3(-0.28f, 0.0f, 0.0f), Rotation(), glm::vec3(1.39f, 1.89f, 1.0f));
    _rect = Rect(transform, glm::vec4(1));
    _renderer = Globals::renderer;
}

void Sim::run() {
    create_imgui_windows();
    create_grid();
    render_cells();
    _renderer->draw_rect(_rect, DrawMode::LINE);
}

void Sim::end() {

}

void Sim::create_imgui_windows() {
    ImGui::Begin("sim bg");
    ImGui::SetWindowSize("window", ImVec2(400, 250));

    ImGui::ColorEdit4("rect color", (float*)&_rect.color);
    ImGui::DragFloat2("rect position", (float*)&_rect.transform.position, 0.01f, -1.0f, 1.0f);
    ImGui::DragFloat2("rect scale", (float*)&_rect.transform.scale, 0.01f, -2.0f, 2.0f);
    ImGui::DragInt("num cells", (int*)&_ncells, 1, 1, 10000);

    // fps
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / Globals::io->Framerate, Globals::io->Framerate);

    ImGui::End();
}

void Sim::create_grid() {
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
}

void Sim::render_cells() {
    for (Cell& cell : _cells) {
        cell.render();
    }
}

