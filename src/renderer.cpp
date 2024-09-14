#include <glad/glad.h>
#include <iostream>

#include "renderer.hpp"


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

void Renderer::draw_point(Point& point) {
    // TODO: clean this up make draw point
    draw_point(point.position);
    push_point_color(point.color);
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

void Renderer::draw_rect(Rect& rect) {
    draw_rect(rect.width, rect.height, rect.position.x, rect.position.y, rect.position.z);
    push_rect_color(rect.color);
}

void Renderer::draw_rect(float width, float height, glm::vec3& position) {
    draw_rect(width, height, position.x, position.y, position.z);
}

void Renderer::draw_rect(float width, float height, float x, float y, float z) {
    glm::vec3 v1(x, y, z);
    glm::vec3 v2(x + width, y, z);
    glm::vec3 v3(x, y - height, z);
    glm::vec3 v4(x + width, y - height, z);
    push_rect(v1, v2, v3, v4);
}

void Renderer::render() {
    update_vbos();
    shaders.point.use();

    glBindVertexArray(_points_vao);
    glDrawArrays(GL_POINTS, 0, _points.size());

    glBindVertexArray(_rects_vao);
    // TODO: check for fill or line mode
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

    _points.clear();
    _rects.clear();
}

void Renderer::push_point(float x, float y, float z) {
    _points.push_back(x);
    _points.push_back(y);
    _points.push_back(z);
}

void Renderer::push_point_color(glm::vec4& color) {
    _points.push_back(color.r);
    _points.push_back(color.g);
    _points.push_back(color.b);
    _points.push_back(color.a);
}

void Renderer::push_rect_point(glm::vec3& point) {
    _rects.push_back(point.x);
    _rects.push_back(point.y);
    _rects.push_back(point.z);
}

void Renderer::push_rect(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3, glm::vec3& v4) {
    push_rect_point(v1);
    push_rect_point(v2);
    push_rect_point(v3);
    push_rect_point(v4);
}

void Renderer::push_rect_color(glm::vec4& color) {
    _rects.push_back(color.r);
    _rects.push_back(color.g);
    _rects.push_back(color.b);
    _rects.push_back(color.a);
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _rects.size(), _rects.data(), GL_STATIC_DRAW);
}

void Renderer::init_vaos() {
    glGenVertexArrays(1, &_points_vao);
    glBindVertexArray(_points_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _points_vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 7, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(float) * 7, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &_rects_vao);
    glBindVertexArray(_rects_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _rects_vbo);

    // TODO: why is this here
    glGenBuffers(1, &_rects_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rects_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _rect_outline_indices.size() * sizeof(float), _rect_outline_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 7, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(float) * 7, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
}

void Renderer::init_shaders() {
    shaders.point.load("shaders/point_shader.vert", "shaders/point_shader.frag");
}

