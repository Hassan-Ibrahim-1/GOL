#pragma once

#include <GLFW/glfw3.h>

namespace InputHandler {

void process_input(GLFWwindow* window, float delta_time);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_movement_callback(GLFWwindow* window, double posx, double posy);
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

}

