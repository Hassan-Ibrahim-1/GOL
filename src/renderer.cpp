#include <glad/glad.h>

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

void Renderer::draw_point(glm::vec3& position) {
    draw_point(position.x, position.y, position.z);
}

void Renderer::draw_point(float x, float y, float z) {
    push_point(x, y, z);
}

void Renderer::reload_shaders() {
    shaders.point.reload();
}

void Renderer::render() {
    update_vbos();
    // glBindBuffer(GL_ARRAY_BUFFER, _points_vbo);
    shaders.point.use();
    glBindVertexArray(_points_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _points_vbo);
    for (const auto& p : _points) {
    //    std::cout << p << '\n';
    }
    glDrawArrays(GL_POINTS, 0, _points.size());
    /*glBindBuffer(GL_ARRAY_BUFFER, _rects_vbo);*/
    /*glDrawArrays(GL_POINTS, 0, _rects.size());*/
}

void Renderer::push_point(float x, float y, float z) {
    _points.push_back(x);
    _points.push_back(y);
    _points.push_back(z);
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

    /*glBindVertexArray(_rects_vao);*/
    /*glBindBuffer(GL_ARRAY_BUFFER, _rects_vbo);*/
    /*glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _rects.size(), _rects.data(), GL_STATIC_DRAW);*/
}

void Renderer::init_vaos() {
    glGenVertexArrays(1, &_points_vao);
    // not sure if this is needed
    glBindVertexArray(_points_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, (void*)0);


    glGenVertexArrays(1, &_rects_vao);
    glBindVertexArray(_rects_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _rects_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, (void*)0);
}

void Renderer::init_shaders() {
    shaders.point.load("shaders/point_shader.vert", "shaders/point_shader.frag");
}

