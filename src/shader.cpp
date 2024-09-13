#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

#include "error_handler.hpp"
#include "imgui.h"

#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    ID = glCreateProgram();

    if (!load_shader_from_path(vertexPath, GL_VERTEX_SHADER)) {
        std::stringstream ss;
        ss << "Bad vertex shader load\n" << _error;
        ErrorHandler::error(ss.str());
        ID = -1;
        return;
    }
    if (!load_shader_from_path(fragmentPath, GL_FRAGMENT_SHADER)) {
        std::stringstream ss;
        ss << "Bad fragment shader load\n" << _error;
        ErrorHandler::error(ss.str());
        ID = -1;
        return;
    }
    glLinkProgram(ID);
    int success = 0;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, _error);
        std::stringstream ss;
        ss << "Bad shader program link\n" << _error;
        ErrorHandler::error(ss.str());
        ID = -1;
        return;
    }
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

bool Shader::check_shader_compilation_success(int shader) {
    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, _error);
        return false;
    }
    return true;
}

bool Shader::load_shader_from_path(const char* path, int flag) {
    int shader = glCreateShader(flag);
    std::string source = get_file_contents(path);
    const char* csrc = source.c_str();
    glShaderSource(shader, 1, &csrc, NULL);
    glCompileShader(shader);
    if (!check_shader_compilation_success(shader)) {
        return false;
    }
    glAttachShader(ID, shader);
    glDeleteShader(shader);
    return true;
}

void Shader::use() {
    glUseProgram(ID);
}

const std::string Shader::get_error() const {
    return _error;
}

std::string Shader::get_file_contents(const char* path) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path);
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        return ss.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "Bad file read: " << e.what() << "\ncode:\n" << e.code() << '\n';
        std::exit(-1);
    }

    // Never reached
    return std::string();
}

void Shader::set_bool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value ? 1 : 0);
}

void Shader::set_int(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_vec3(const std::string& name, glm::vec3& value) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::set_vec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::set_vec3(const std::string& name, ImVec4& value) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::set_mat4(const std::string& name, glm::mat4& value) const {
    // glm::value_ptr gets glsl compatible values
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

