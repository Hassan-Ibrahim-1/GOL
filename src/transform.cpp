#include <glm/gtc/matrix_transform.hpp>

#include "transform.hpp"

Rotation::Rotation(float yaw, float pitch, float roll)
    : yaw(yaw),
      pitch(pitch),
      roll(roll) {}

Transform::Transform(glm::vec3 position, Rotation rotation, glm::vec3 scale)
    : position(position),
      rotation(rotation),
      scale(scale) {}

