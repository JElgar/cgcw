#include "Light.h"

Light::Light(glm::vec3 position) {
  _position = position;
}

ModelPoint Light::position() {
  return ModelPoint(_position);
}
