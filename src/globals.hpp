#pragma once

#include "imgui.h"

#include "camera.hpp"
#include "shader.hpp"

struct Shaders {
    Shaders();
    Shader point;
    // Shader rect;
};

namespace Globals {

inline Camera g_camera;
inline ImGuiIO* g_io = nullptr;
}

