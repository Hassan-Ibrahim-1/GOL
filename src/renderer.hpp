#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "common.hpp"
#include "point.hpp"
#include "shader.hpp"

enum class DrawMode {
    FILL,
    LINE,
};

class Renderer {
public:
    struct Shaders {
        Shaders() = default;
        Shader point;
    } shaders;

    Renderer();
    ~Renderer();

    void draw_point(Point& point);
    void draw_point(glm::vec3 position, glm::vec4 color);

    void draw_rect(Rect& rect, DrawMode draw_mode = DrawMode::FILL);
    void draw_rect(float width, float height, glm::vec3 position, glm::vec4 color);

    void reload_shaders();

    // Actually render all draw calls
    void render();

private:
    std::vector<float> _points;
    std::vector<Rect> _rects;
    std::vector<DrawMode> _rect_draw_modes;

    uint _points_vao;
    uint _points_vbo;
    uint _rects_vao;
    uint _rects_vbo;
    uint _rects_ebo;

    static constexpr std::array<uint, 8> _rect_outline_indices = {
        0, 1,
        1, 3,
        0, 2,
        2, 3,
    };

    static constexpr std::array<float, 12> _rect_vertices = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, // bottom left
       -0.5f, 0.5f, 0.0f // top left
    };

    static constexpr std::array<uint, 6> _rect_indices = {
        0, 1, 3,
        1, 2, 3 
    };

    void push_point(float x, float y, float z);
    void push_point_color(glm::vec4& color);

    void init_vbos();
    void update_vbos();
    void init_vaos();
    // void update_vaos();
    // initializes shaders needed by the renderer
    void init_shaders();
};

