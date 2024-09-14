#pragma once

#include <glm/glm.hpp>
#include "imgui.h"

namespace Utils {

glm::vec3 imvec4_to_glm_vec3(ImVec4& vec);
glm::vec4 imvec4_to_glm_vec4(ImVec4& vec);

ImVec4 glm_vec3_to_imvec4(glm::vec3& vec);
ImGuiIO& create_imgui_context();

}

