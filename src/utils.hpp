#pragma once

#include <glm/glm.hpp>
#include "imgui.h"

#include "transform.hpp"

namespace Utils {

void init();

glm::vec3 imvec4_to_glm_vec3(ImVec4& vec);
glm::vec4 imvec4_to_glm_vec4(ImVec4& vec);

ImVec4 glm_vec3_to_imvec4(glm::vec3& vec);
ImGuiIO& create_imgui_context();

float random_float(float min, float max);

float noise(int x, int y);

// TODO:
void add_to_imgui(Transform& transform);

}

