#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "common.hpp"
#include "shader.hpp"

class Renderer {
public:
    Renderer();

    void draw_point(glm::vec3& position);
    void draw_point(float x, float y, float z);

    void draw_rect(float width, float height, glm::vec3 position);
    void draw_rect(float width, float height, float x, float y, float z);

    // Actually render all draw calls
    void render();

private:
    std::vector<float> _points;
    std::vector<float> _rects;


    struct Shaders {
        Shaders() = default;
        Shader point;
        // Shader rect;
    } shaders;
    // Shaders shaders = Shaders();

    uint _points_vao;
    uint _points_vbo;
    uint _rects_vao;
    uint _rects_vbo;

    void push_point(float x, float y, float z);
    void init_vbos();
    void update_vbos();
    void init_vaos();
    // void update_vaos();
    // initializes shaders needed by the renderer
    void init_shaders();
};

