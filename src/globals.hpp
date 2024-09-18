#pragma once

#include "imgui.h"

#include "camera.hpp"
#include "renderer.hpp"

namespace Globals {

inline Camera camera;
inline ImGuiIO* io = nullptr;
inline Renderer* renderer;
inline glm::vec2 mouse_pos = glm::vec2(0);

}

