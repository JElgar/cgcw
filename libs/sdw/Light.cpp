#include "Light.h"

ModelPoint Light::position() {
  return ModelPoint(_position);
}

float Light::intensity() {
  return _intensity;
}

void Light::translate(glm::vec3 translation) {
  _position += translation;
}
