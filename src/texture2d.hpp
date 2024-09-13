#pragma once

#include <glad/glad.h>

#include <string>

#include "common.hpp"

class Texture2D {
public:
    uint ID = 0;
    int width = 0;
    int height = 0;
    int nr_channels = 0;

    Texture2D(const std::string& path);
    ~Texture2D(); // automatically unloads texture

    // automatically generates a mipmap
    void load(int channel_flag = GL_RGB, bool default_texture_sampling = true);
    // manually unload a texture
    void unload();
    
    // Binds the texture in opengl
    void bind();

    // Enables some default texture sampling in opengl
    void enable_default_texture_sampling();

private:
    std::string _path;
    u8* _data;
    bool _texture_loaded = false;
};

