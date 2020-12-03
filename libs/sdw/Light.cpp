#include "Light.h"

Light::Light(glm::vec3 position) {
  _position = position;
}

glm::vec3 Light::position() {
  return _position;
}
