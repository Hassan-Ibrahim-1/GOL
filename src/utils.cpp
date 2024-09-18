#include <ctime>

#include "utils.hpp"

void Utils::init() {
    srand (static_cast<unsigned> (time(0)));
}

glm::vec3 Utils::imvec4_to_glm_vec3(ImVec4& vec) {
    return glm::vec3(vec.x, vec.y, vec.z);
}

glm::vec4 Utils::imvec4_to_glm_vec4(ImVec4& vec) {
    return glm::vec4(vec.x, vec.y, vec.z, vec.w);
}

ImVec4 Utils::glm_vec3_to_imvec4(glm::vec3& vec) {
    return ImVec4(vec.x, vec.y, vec.z, 0);
}

ImGuiIO& Utils::create_imgui_context() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io; // what
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    return io;
}

float Utils::random_float(float min, float max) {
    return min + static_cast<float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

