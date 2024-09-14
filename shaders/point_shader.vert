#version 410 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;

out vec4 color;

void main() {
    gl_Position = vec4(position, 1.0f);
    color = a_color;
}

