#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "error_handler.hpp"
#include "input_handler.hpp"
#include "renderer.hpp"
#include "settings.hpp"
#include "sim.hpp"
#include "utils.hpp"
#include "window.hpp"
#include "globals.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

static void cleanup();

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    #endif

    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Bebe");

    glfwSetInputMode(window.get_window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if (ErrorHandler::had_error) {
        cleanup();
        return -1;
    }

    glfwSetKeyCallback(window.get_window(), InputHandler::key_callback);
    glfwSetCursorPosCallback(window.get_window(), InputHandler::mouse_movement_callback);
    /*glfwSetScrollCallback(window.get_window(), InputHandler::mouse_scroll_callback);*/

    // Enable vsync
    glfwSwapInterval(1);

    // imgui stuff
    const char* glsl_version = "#version 410";
    
    // imgui context
    ImGuiIO& io = Utils::create_imgui_context();
    Globals::io = &io;

    ImGui::StyleColorsDark();

    // setup renderer
    ImGui_ImplGlfw_InitForOpenGL(window.get_window(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    float delta_time = 0.0f;
    float last_frame = 0.0f;

    glEnable(GL_DEPTH_TEST);

    Renderer renderer;
    Globals::renderer = &renderer;

    Camera& camera = Globals::camera;
    camera = Camera(glm::vec3(0.0f, 0.0f, 1.0f));

    Sim::init();

    // imgui state
    ImVec4 point_color(1.0f, 0.0f, 0.0f, 1.0f);
    bool rect_fill = true;
    ImVec4 position(0.0f, 0.0f, 0.0f, 0.0f);
    ImVec4 scale(1.0f, 1.0f, 1.0f, 0.0f);

    while (!glfwWindowShouldClose(window.get_window())) {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        if (glfwGetWindowAttrib(window.get_window(), GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        /*if (Settings::wireframe_enabled) {*/
        /*    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
        /*}*/
        /*else {*/
        /*    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/
        /*}*/

        // start imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glm::mat4 view = camera.get_view_matrix();
        renderer.shaders.point.set_mat4("view", view);

        Sim::run();

        // render imgui windows
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        renderer.render();

        glfwSwapBuffers(window.get_window());
        glfwPollEvents();
    }
    cleanup();
}

static void cleanup() {
    Sim::end();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

