#include <glm/glm.hpp>

#include "sim.hpp"
#include "globals.hpp"

void Sim::init() {
    Transform transform(glm::vec3(-0.28f, 0.0f, 0.0f), Rotation(), glm::vec3(1.39f, 1.89f, 1.0f));
    _rect = Rect(transform, glm::vec4(1));
    _renderer = Globals::renderer;
}

void Sim::run() {
    create_imgui_windows();
    _renderer->draw_rect(_rect, DrawMode::LINE);
}

void Sim::create_imgui_windows() {
    ImGui::Begin("sim bg");
    ImGui::SetWindowSize("window", ImVec2(400, 250));
    ImGui::ColorEdit4("point color", (float*)&_rect.color.a, (float*)_rect.color.b);
    /*ImGui::DragFloat2("position", (float*)&position, 0.01f, -1.0f, 1.0f);*/
    /*ImGui::DragFloat2("scale", (float*)&scale, 0.01f, -2.0f, 2.0f);*/
    // fps
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}

void Sim::end() {

}

