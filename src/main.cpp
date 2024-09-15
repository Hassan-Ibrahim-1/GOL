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
#include "utils.hpp"
#include "window.hpp"
#include "globals.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define IMGUI_WINDOW_WIDTH 400
#define IMGUI_WINDOW_HEIGHT 250

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

    if (ErrorHandler::had_error) {
        cleanup();
        return -1;
    }

    glfwSetKeyCallback(window.get_window(), InputHandler::key_callback);
    /*glfwSetCursorPosCallback(window.get_window(), InputHandler::mouse_movement_callback);*/
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

    // check for shader error
    if (ErrorHandler::had_error) {
        cleanup();
        return -1;
    }

    if (ErrorHandler::had_error) {
        cleanup();
        return -1;
    }

    float delta_time = 0.0f;
    float last_frame = 0.0f;

    glEnable(GL_DEPTH_TEST);

    Renderer renderer;
    Globals::renderer = &renderer;

    Camera& camera = Globals::camera;
    camera = Camera(glm::vec3(0.0f, 0.0f, 1.0f));

    // glm::mat4 projection = glm::perspective(0.0f, (float) WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 projection(1);
    projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    renderer.shaders.point.set_mat4("projection", projection);

    // imgui state
    ImVec4 point_color(1.0f, 0.0f, 0.0f, 1.0f);
    bool rect_fill = true;
    ImVec4 position(0.0f, 0.0f, 0.0f, 0.0f);
    ImVec4 scale(1.0f, 1.0f, 1.0f, 0.0f);

    while (!glfwWindowShouldClose(window.get_window())) {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        InputHandler::process_input(window.get_window(), delta_time);

        if (glfwGetWindowAttrib(window.get_window(), GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        if (Settings::wireframe_enabled) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // start imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("config");
        ImGui::SetWindowSize("window", ImVec2(IMGUI_WINDOW_WIDTH, IMGUI_WINDOW_HEIGHT));
        ImGui::ColorEdit4("point color", (float*)&point_color);
        ImGui::Checkbox("fill", &rect_fill);
        ImGui::DragFloat2("position", (float*)&position, 0.01f, -1.0f, 1.0f);
        ImGui::DragFloat2("scale", (float*)&scale, 0.01f, -1.0f, 1.0f);
        // fps
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glm::mat4 view = camera.get_view_matrix();
        renderer.shaders.point.set_mat4("view", view);

        glm::vec3 rect_position = Utils::imvec4_to_glm_vec3(position);
        glm::vec3 rect_scale = Utils::imvec4_to_glm_vec3(scale);
        glm::vec4 color = Utils::imvec4_to_glm_vec4(point_color);

        Transform transform(rect_position, Rotation(), rect_scale);
        Rect rect(transform, color);
        renderer.draw_rect(rect, rect_fill ? DrawMode::FILL : DrawMode::LINE);

        Transform transform2(glm::vec3(0), Rotation(), glm::vec3(1));
        Rect rect2(transform2, glm::vec4(1));
        renderer.draw_rect(rect2, !rect_fill ? DrawMode::FILL : DrawMode::LINE);

        renderer.render();

        // render imgui windows
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window.get_window());
        glfwPollEvents();
    }
    cleanup();
}

static void cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

