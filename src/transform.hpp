#pragma once

#include <glm/glm.hpp>

struct Rotation {
    float yaw;
    float pitch;
    float roll;

    Rotation(float yaw = 0.0f, float pitch = 0.0f, float roll = 0.0f);
};

struct Transform {
public:
    glm::vec3 position;
    Rotation rotation;
    glm::vec3 scale;

    Transform(glm::vec3 position = glm::vec3(),
              Rotation rotation = Rotation(),
              glm::vec3 scale = glm::vec3(1));

    // only factors in position and scale rn
    glm::mat4 get_mat4();
};

