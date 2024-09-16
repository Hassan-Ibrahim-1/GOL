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
    // Cell cell(glm::vec3(_rect.transform.position.x / 2, _rect.transform.position.y / 2, 1), glm::vec4(1));
    std::vector<Cell> cells;

    uint f1 = (int) glm::sqrt(n_cells);
    uint f2 = f1;
    for (; f2 * f1 != n_cells; f2++) {
        if (f2  > 1000) {
            ErrorHandler::error("no factor found below 1000");
            std::exit(-1);
            break;
        }
    }
    printf("f1: %d, f2: %d\n", f1, f2);
}

