#include "GLFW/glfw3.h"

#include "globals.hpp"
#include "settings.hpp"
#include "camera.hpp"

#include "input_handler.hpp"

static float last_mouse_x = 0.0f;
static float last_mouse_y = 0.0f;
static bool first_mouse = true; // corrects for a large initial jump

void InputHandler::process_input(GLFWwindow* window, float delta_time) {
    Camera& camera = Globals::camera;

    /*if (Globals::io->WantTextInput) return;*/

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.process_keyboard(CameraDirection::UP, delta_time);
        /*glfwSetWindowShouldClose(window, true);*/
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.process_keyboard(CameraDirection::DOWN, delta_time);
        /*glfwSetWindowShouldClose(window, true);*/
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.process_keyboard(CameraDirection::FORWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.process_keyboard(CameraDirection::BACKWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.process_keyboard(CameraDirection::RIGHT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.process_keyboard(CameraDirection::LEFT, delta_time);
    }
}

void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        /*if (Settings::cursor_enabled) {*/
        /*    Settings::cursor_enabled = false;*/
        /*}*/
        /*else {*/
        glfwSetWindowShouldClose(window, true);
        /*}*/
    }

    /*if (Globals::io->WantTextInput) {*/
    /*    return;*/
    /*}*/
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        Settings::wireframe_enabled = !Settings::wireframe_enabled;
    }
    // enable / disable cursor
    /*if (key == GLFW_KEY_2 && action == GLFW_PRESS) {*/
    /*    Settings::cursor_enabled = !Settings::cursor_enabled;*/
    /*}*/
}

void InputHandler::mouse_movement_callback(GLFWwindow* window, double posx, double posy) {
    if (Settings::cursor_enabled) {
        last_mouse_x = posx;
        last_mouse_y = posy;
        return;
    }
    if (first_mouse) {
        last_mouse_x = posx;
        last_mouse_y = posy;
        first_mouse = false;
    }
    float x_offset = posx - last_mouse_x;
    float y_offset = posy - last_mouse_y;
    last_mouse_x = posx;
    last_mouse_y = posy;

    Globals::camera.process_mouse_movement(x_offset, y_offset);
}

void InputHandler::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (Settings::cursor_enabled) return;

    Globals::camera.process_mouse_scroll(yoffset);
}

