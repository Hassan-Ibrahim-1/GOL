#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <iostream>

#include "renderer.hpp"
#include "error_handler.hpp"

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
    draw_point(point.position, point.color);
}

void Renderer::draw_point(glm::vec3 position, glm::vec4 color) {
    push_point(position.x, position.y, position.z);
    push_point_color(color);
}

void Renderer::reload_shaders() {
    shaders.point.reload();
}

void Renderer::draw_rect(Rect& rect, DrawMode draw_mode) {
    /*draw_rect(rect.width, rect.height, rect.position, rect.color);*/
    _rects.push_back(rect);
    _rect_draw_modes.push_back(draw_mode);
}

void Renderer::draw_rect(float width, float height, glm::vec3 position, glm::vec4 color) {
    glm::vec3 v1(position.x, position.y, position.z);
    glm::vec3 v2(position.x + width, position.y, position.z);
    glm::vec3 v3(position.x, position.y - height, position.z);
    glm::vec3 v4(position.x + width, position.y - height, position.z);
    push_rect(v1, v2, v3, v4, color);
}

void Renderer::render() {
    update_vbos();
    shaders.point.use();

    glBindVertexArray(_points_vao);
    glDrawArrays(GL_POINTS, 0, _points.size());

    glBindVertexArray(_rects_vao);
    size_t i = 0;
    for (; i < _rects.size(); i++) {
        Rect& rect = _rects[i];
        DrawMode draw_mode = _rect_draw_modes[i];

        glm::mat4 model(1);
        model = glm::translate(model, rect.transform.position);
        model = glm::scale(model, rect.transform.scale);
        shaders.point.set_mat4("model", model);
        shaders.point.set_vec4("color", rect.color);

        if (draw_mode == DrawMode::FILL) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        else if (draw_mode == DrawMode::LINE) {
            glDrawArrays(GL_LINE_LOOP, 0, 4);
        }
    }
    std::cout << "i: " << i << '\n';
    _points.clear();
    _rects.clear();
    _rect_draw_modes.clear();
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

void Renderer::push_rect(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3, glm::vec3& v4, glm::vec4& color) {
    push_rect_point(v1);
    push_rect_color(color);
    push_rect_point(v2);
    push_rect_color(color);
    push_rect_point(v3);
    push_rect_color(color);
    push_rect_point(v4);
    push_rect_color(color);
}

void Renderer::push_rect_point(glm::vec3& point) {
    /*_rects.push_back(point.x);*/
    /*_rects.push_back(point.y);*/
    /*_rects.push_back(point.z);*/
}

void Renderer::push_rect_color(glm::vec4& color) {
    /*_rects.push_back(color.r);*/
    /*_rects.push_back(color.g);*/
    /*_rects.push_back(color.b);*/
    /*_rects.push_back(color.a);*/
}

void Renderer::init_vbos() {
    glGenBuffers(1, &_points_vbo);
    glGenBuffers(1, &_rects_vbo);
}

void Renderer::update_vbos() {
    glBindVertexArray(_points_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _points.size(), _points.data(), GL_STATIC_DRAW);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _rect_vertices.size(), _rect_vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &_rects_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rects_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * _rect_indices.size(), _rect_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    /*glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(float) * 7, (void*)(sizeof(float) * 3));*/
    /*glEnableVertexAttribArray(1);*/
}

void Renderer::init_shaders() {
    shaders.point.load("shaders/point_shader.vert", "shaders/point_shader.frag");
}

