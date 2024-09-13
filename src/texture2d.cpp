#include <glad/glad.h>

#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "error_handler.hpp"

#include "texture2d.hpp"

Texture2D::Texture2D(const std::string& path)
    : _path(path) {
    stbi_set_flip_vertically_on_load(true);
}

Texture2D::~Texture2D() {
    unload();
}

void Texture2D::load(int channel_flag, bool default_texture_sampling) {
    glGenTextures(1, &ID);
    bind();
    if (default_texture_sampling) {
        enable_default_texture_sampling();
    }

    _data = stbi_load(_path.c_str(), &width, &height, &nr_channels, 0);
    
    if (_data == nullptr) {
        std::stringstream ss;
        ss << "Bad image load - path: " << _path;
        ErrorHandler::error(ss.str());
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, channel_flag, width, height, 0, channel_flag, GL_UNSIGNED_BYTE, _data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(_data);
    _texture_loaded = true;
}

void Texture2D::unload() {
    if (_texture_loaded) {
        glDeleteTextures(1, &ID);
        _texture_loaded = false;
    }
}

void Texture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::enable_default_texture_sampling() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

