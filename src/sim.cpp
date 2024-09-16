#include <glm/glm.hpp>

#include "sim.hpp"
#include "cell.hpp"
#include "error_handler.hpp"
#include "globals.hpp"
#include "imgui.h"

void Sim::init() {
    Transform transform(glm::vec3(-0.28f, 0.0f, 0.0f), Rotation(), glm::vec3(1.39f, 1.89f, 1.0f));
    _rect = Rect(transform, glm::vec4(1));
    _renderer = Globals::renderer;
}

void Sim::run() {
    create_imgui_windows();
    create_rect_grid();
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
    ImGui::DragInt("num cells", (int*)&n_cells, 1, 1, 1000);

    // fps
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / Globals::io->Framerate, Globals::io->Framerate);

    ImGui::End();
}

void Sim::create_rect_grid() {
    std::vector<Cell> cells;

    // Find the closest factors
    uint f1 = (uint) glm::sqrt(n_cells); //
    while (n_cells % f1 != 0) {
        f1--;
    }
    // f2 > f1
    uint f2 = n_cells / f1; // along the width
    printf("f1: %u, f2: %u\n", f1, f2);

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
    printf("rows: %u, cols: %u\n", n_rows, n_cols);

    // TODO: figure out width
}

