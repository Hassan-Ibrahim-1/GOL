#pragma once

#include "imgui.h"

#include "rect.hpp"
#include "renderer.hpp"

namespace Sim {

inline Rect _rect;
inline Renderer* _renderer;

// imgui state variables
inline ImVec4 _rect_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

void init();
void run();
void end();

void create_imgui_windows();

}

