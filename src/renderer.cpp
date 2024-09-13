#include <glad/glad.h>
#include <iostream>

#include "renderer.hpp"

float vertices[] =  {
    0.5f, 0.5f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, 0.5f, 0.0f, // top left
    // second triangle
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f // top left
};

Renderer::Renderer() {
    init_vbos();
    init_vaos();
    init_shaders();
}

Renderer::~Renderer() {
    glDeleteBuffers(1, &_points_vbo);
    glDeleteBuffers(1, &_rects_vbo);
    glDeleteVertexArrays(1, &_points_vao);
    glDeleteVertexArrays(1, &_rects_vao);
}

void Renderer::draw_point(glm::vec3& position) {
    draw_point(position.x, position.y, position.z);
}

void Renderer::draw_point(float x, float y, float z) {
    push_point(x, y, z);
}

void Renderer::reload_shaders() {
    shaders.point.reload();
}

void Renderer::draw_rect(float width, float height, glm::vec3& position) {
    draw_rect(width, height, position.x, position.y, position.z);
}

void Renderer::draw_rect(float width, float height, float x, float y, float z) {
    glm::vec3 v1(x, y, z);
    glm::vec3 v2(x + width, y, z);
    glm::vec3 v3(x, y + height, z);
    glm::vec3 v4(x + width, y + height, z);
    push_rect(v1, v2, v3, v4);
}

void Renderer::render() {
    update_vbos();
    shaders.point.use();
    glBindVertexArray(_points_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _points_vbo);
    for (const auto& p : _points) {
    //    std::cout << p << '\n';
    }
    glDrawArrays(GL_POINTS, 0, _points.size());

    // glEnable(GL_SCISSOR_TEST);:w
    // glScissor(0, 0, 1, 1);
    /*glBindBuffer(GL_ARRAY_BUFFER, _rects_vbo);*/
    shaders.point.use();
    glBindVertexArray(_rects_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _rects_vbo);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    _points.clear();
    _rects.clear();
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::push_point(float x, float y, float z) {
    _points.push_back(x);
    _points.push_back(y);
    _points.push_back(z);
}

void Renderer::push_rect(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3, glm::vec3& v4) {
    push_rect_point(v1);
    push_rect_point(v2);
    push_rect_point(v3);
    push_rect_point(v4);
}

void Renderer::push_rect_point(glm::vec3& point) {
    _rects.push_back(point.x);
    _rects.push_back(point.y);
    _rects.push_back(point.z);
}

void Renderer::init_vbos() {
    glGenBuffers(1, &_points_vbo);
    glGenBuffers(1, &_rects_vbo);
}

void Renderer::update_vbos() {
    // not sure if this is needed
    glBindVertexArray(_points_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _points.size(), _points.data(), GL_STATIC_DRAW);

    glBindVertexArray(_rects_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _rects_vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _rects.size(), _rects.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Renderer::init_vaos() {
    glGenVertexArrays(1, &_points_vao);
    // not sure if this is needed
    glBindVertexArray(_points_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &_rects_vao);
    glBindVertexArray(_rects_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _rects_vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);
}

void Renderer::init_shaders() {
    shaders.point.load("shaders/point_shader.vert", "shaders/point_shader.frag");
}

