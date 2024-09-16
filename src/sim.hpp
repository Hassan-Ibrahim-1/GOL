#pragma once

#include "rect.hpp"
#include "renderer.hpp"

namespace Sim {

inline Rect _rect;
// inline Transform _rect_transform = Transform(glm::vec3(-0.28f, 0.0f, 0.0f), Rotation(), glm::vec3(1.39f, 1.89f, 1.0f));
inline Renderer* _renderer;

void init();
void run();
void end();

void create_imgui_windows();

}

